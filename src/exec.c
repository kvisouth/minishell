/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/04/24 18:18:33 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	end(int code, bool kill, char *msg)
{
	g_sig = code;
	if (kill == TRUE)
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		exit(code);
	}
	else
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
	}
}

void	exec_builtin(t_shell *shell, t_simple_cmds *cmd)
{
	if (ft_strcmp(cmd->str[0], "env") == 0)
		builtin_env(shell->env);
	else if (ft_strcmp(cmd->str[0], "cd") == 0)
		builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->str[0], "echo") == 0)
		builtin_echo(cmd->str);
	else if (ft_strcmp(cmd->str[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->str[0], "export") == 0)
		builtin_export(shell, cmd);
	else if (ft_strcmp(cmd->str[0], "unset") == 0)
		builtin_unset(shell, cmd);
}

int	cmd_have_no_path(char *cmd)
{
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.') || ft_strchr(cmd, '~'))
		return (0);
	return (1);
}

void	count_cmds(t_shell *shell)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = shell->simple_cmds;
	while (tmp)
	{
		i++;
		tmp->index = i;
		tmp = tmp->next;
	}
	shell->nb_cmds = i;
}

void	format_cmds(t_shell *shell)
{
	t_simple_cmds	*cmd;

	cmd = shell->simple_cmds;
	while (cmd)
	{
		if (cmd->builtin == false)
		{
			if (cmd_have_no_path(cmd->str[0]))
			{
				if (!add_path_to_cmd(shell, cmd))
					return ;
			}
		}
		cmd = cmd->next;
	}
}

void	handle_redirections(t_simple_cmds *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}				
		redir = redir->next;
	}
}

void	execute_builtin(t_shell *shell, t_simple_cmds *cmd)
{
	int	restore_stdin;
	int	restore_stdout;

	restore_stdin = dup(STDIN_FILENO);
	restore_stdout = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	exec_builtin(shell, cmd);
	dup2(restore_stdin, STDIN_FILENO);
	dup2(restore_stdout, STDOUT_FILENO);
	close(restore_stdin);
	close(restore_stdout);
}

void	child_process(t_shell *shell, t_simple_cmds *cmd)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
	{
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
			exit(127);
	}
	else
		waitpid(cmd->pid, &status, 0);
}

void	handle_child_process(t_shell *shell,
		t_simple_cmds *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipefd != NULL && cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	handle_redirections(cmd);
	if (cmd->builtin)
	{
		exec_builtin(shell, cmd);
		exit(0);
	}
	else
	{
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
			exit(1);
	}
	exit(0);
}

void	handle_parent_process(int *prev_fd, int pipefd[2], t_simple_cmds *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
		close(pipefd[1]);
	if (cmd->next)
		*prev_fd = pipefd[0];
	else
		*prev_fd = -1;
}

int	execute_command(t_shell *shell, t_simple_cmds *cmd)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = -1;
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit(1);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
	{
		if (cmd->next)
			handle_child_process(shell, cmd, prev_fd, pipefd);
		else
			handle_child_process(shell, cmd, prev_fd, NULL);
	}
	if (cmd->next)
	{
		close(pipefd[1]);
		prev_fd = pipefd[0];
	}
	else
		prev_fd = -1;
	while (waitpid(cmd->pid, NULL, 0) > 0)
		;
	return (0);
}

void	execute_pipeline(t_shell *shell)
{
	int				pipefd[2];
	int				prev_fd;
	t_simple_cmds	*cmd;

	prev_fd = -1;
	cmd = shell->simple_cmds;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
				exit(1);
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(1);
		if (cmd->pid == 0)
			handle_child_process(shell, cmd, prev_fd, pipefd);
		handle_parent_process(&prev_fd, pipefd, cmd);
		cmd = cmd->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

int	exec(t_shell *shell)
{
	int	restore_stdout;

	restore_stdout = dup(STDOUT_FILENO);
	count_cmds(shell);
	format_cmds(shell);
	if (shell->nb_cmds > 1)
		execute_pipeline(shell);
	else
	{
		if (shell->simple_cmds->builtin)
			execute_builtin(shell, shell->simple_cmds);
		else
			execute_command(shell, shell->simple_cmds);
	}
	dup2(restore_stdout, STDOUT_FILENO);
	close(restore_stdout);
	return (0);
}

//TODO : gerer les codes d'erreurs
//TODO : faire exit
//TODO : gerer les redirections < et <<