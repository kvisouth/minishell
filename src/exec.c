/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/05/17 13:52:15 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_signals_for_parent_with_children(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals_for_parent(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	end(int code, bool kill, char *msg)
{
	g_sig = code;
	if (kill == TRUE)
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		else
			perror("Error");
		exit(code);
	}
	else
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		else
			perror("Error");
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
	else if (ft_strcmp(cmd->str[0], "exit") == 0)
		builtin_exit(cmd->str);
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

/* Append the path to every non-builtin command */
void	format_cmds(t_shell *shell)
{
	t_simple_cmds	*cmd;

	cmd = shell->simple_cmds;
	while (cmd)
	{
		if (!cmd->str[0])
		{
			cmd = cmd->next;
			continue ;
		}
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

void	child_process_heredoc(t_simple_cmds *cmd)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_DFL);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->redirects->file) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(line);
	exit(0);
}

void	handle_redir_heredoc(t_simple_cmds *cmd)
{
	pid_t	heredoc_pid;
	int		fd;
	int		status;

	set_signals_for_parent_with_children();
	heredoc_pid = fork();
	if (heredoc_pid == -1)
		end(1, TRUE, "fork failed");
	if (heredoc_pid == 0)
		child_process_heredoc(cmd);
	waitpid(heredoc_pid, &status, 0);
	reset_signals_for_parent();
	if (WIFSIGNALED(status))
	{
		g_sig = 128 + WTERMSIG(status);
		return ;
	}
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
		end(1, TRUE, "open failed");
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heredoc");
}

void	handle_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redirections(t_simple_cmds *cmd)
{
	t_redir	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			handle_redir_append(redir);
		else if (redir->type == REDIR_IN)
			handle_redir_in(redir);
		else if (redir->type == REDIR_HEREDOC)
			handle_redir_heredoc(cmd);
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

void	handle_child_process(t_shell *shell,
		t_simple_cmds *cmd, int prev_fd, int pipefd[2])
{
	set_signals_for_child();
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
	else if (cmd->str[0] != NULL && cmd->builtin == false)
	{
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
		{
			if (access(cmd->str[0], X_OK) == 0 || access(cmd->str[0], F_OK) == 0
				|| access(cmd->str[0], R_OK) == 0)
				end(126, TRUE, "Error: permission denied\n");
			else
				end(127, TRUE, "Error: command not found\n");
		}
	}
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

void	wait_for_children(int last_pid)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status))
		{
			if (pid == last_pid)
				g_sig = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			if (pid == last_pid)
				g_sig = 128 + WTERMSIG(status);
		}
		pid = waitpid(-1, &status, 0);
	}
}

void	setup_pipes(t_simple_cmds *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit(1);
	}
}

int	execute_command(t_shell *shell, t_simple_cmds *cmd)
{
	int	pipefd[2];
	int	prev_fd;
	int	status;

	prev_fd = -1;
	setup_pipes(cmd, pipefd);
	set_signals_for_parent_with_children();
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
	{
		set_signals_for_child();
		handle_child_process(shell, cmd, prev_fd, NULL);
	}
	if (cmd->next)
	{
		close(pipefd[1]);
		prev_fd = pipefd[0];
	}
	else
		prev_fd = -1;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_sig = WEXITSTATUS(status);
	}
	reset_signals_for_parent();
	return (0);
}

void	execute_pipeline(t_shell *shell)
{
	int				pipefd[2];
	int				prev_fd;
	t_simple_cmds	*cmd;
	int				last_pid;

	prev_fd = -1;
	cmd = shell->simple_cmds;
	set_signals_for_parent_with_children();
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
		{
			set_signals_for_child();
			handle_child_process(shell, cmd, prev_fd, pipefd);
		}
		handle_parent_process(&prev_fd, pipefd, cmd);
		if (!cmd->next)
			last_pid = cmd->pid;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
	reset_signals_for_parent();
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

// TODO : Le parent doit ignorer les signaux des lors qu'un enfant
//        est en cours d'execution
// TODO : Finir heredoc
// TODO : TOUT FREE a l'utilisation de end() (parser + lexer?)
