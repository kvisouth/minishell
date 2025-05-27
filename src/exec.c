/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/05/27 18:35:04 by kevisout         ###   ########.fr       */
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

void	write_end_of_heredoc(int fd, char *expanded)
{
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
}

void	child_process_heredoc(char *delimiter, char *filename, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*expanded;

	signal(SIGINT, SIG_DFL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, shell->env);
		free(line);
		if (!expanded)
			exit(1);
		write_end_of_heredoc(fd, expanded);
		free(expanded);
	}
	close(fd);
	exit(0);
}

int	process_one_heredoc(t_redir *redir, t_shell *shell)
{
	pid_t	heredoc_pid;
	int		status;
	char	*filename;

	filename = ft_strdup(".heredoc");
	if (!filename)
		return (0);
	set_signals_for_parent_with_children();
	heredoc_pid = fork();
	if (heredoc_pid == -1)
		return (free(filename), 0);
	if (heredoc_pid == 0)
		child_process_heredoc(redir->file, filename, shell);
	waitpid(heredoc_pid, &status, 0);
	reset_signals_for_parent();
	if (WIFSIGNALED(status))
	{
		g_sig = 128 + WTERMSIG(status);
		free(filename);
		return (0);
	}
	redir->heredoc_file = filename;
	return (1);
}

int	process_all_heredocs(t_shell *shell)
{
	t_simple_cmds	*cmd;
	t_redir			*redir;

	cmd = shell->simple_cmds;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (!process_one_heredoc(redir, shell))
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

void	handle_redir_heredoc(t_redir *redir)
{
	int	fd;

	fd = open(redir->heredoc_file, O_RDONLY);
	if (fd == -1)
		end(1, TRUE, "open failed");
	dup2(fd, STDIN_FILENO);
	close(fd);
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
			handle_redir_heredoc(redir);
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

void	handle_execve_error(t_simple_cmds *cmd)
{
	if (access(cmd->str[0], X_OK) == 0 || access(cmd->str[0], F_OK) == 0
		|| access(cmd->str[0], R_OK) == 0)
		end(126, TRUE, "Error: Permission denied\n");
	else
		end(127, TRUE, "Error: command not found\n");
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
			handle_execve_error(cmd);
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

void	wait_for_command(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			g_sig = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sig = 128 + WTERMSIG(status);
		pid = waitpid(-1, &status, 0);
	}
}

void	execute_command(t_shell *shell, t_simple_cmds *cmd)
{
	int	pipefd[2];
	int	prev_fd;

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
	wait_for_command();
	reset_signals_for_parent();
}

void	init_pipeline(int *prev_fd, t_simple_cmds **cmd, t_shell *shell)
{
	*prev_fd = -1;
	*cmd = shell->simple_cmds;
	set_signals_for_parent_with_children();
}

void	create_pipe_for_cmd(t_simple_cmds *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit(1);
	}
}

void	fork_and_execute_cmd(t_shell *shell, t_simple_cmds *cmd,
							int prev_fd, int pipefd[2])
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
	{
		set_signals_for_child();
		handle_child_process(shell, cmd, prev_fd, pipefd);
	}
}

void	execute_pipeline(t_shell *shell)
{
	int				pipefd[2];
	int				prev_fd;
	t_simple_cmds	*cmd;
	int				last_pid;

	init_pipeline(&prev_fd, &cmd, shell);
	while (cmd)
	{
		create_pipe_for_cmd(cmd, pipefd);
		fork_and_execute_cmd(shell, cmd, prev_fd, pipefd);
		handle_parent_process(&prev_fd, pipefd, cmd);
		if (!cmd->next)
			last_pid = cmd->pid;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
	reset_signals_for_parent();
}

void	unlink_heredoc(void)
{
	if (access(".heredoc", F_OK) == -1)
		return ;
	if (unlink(".heredoc") == 1)
	{
		perror("Error unlinking .heredoc");
		exit(1);
	}
}

int	exec(t_shell *shell)
{
	int	restore_stdout;

	restore_stdout = dup(STDOUT_FILENO);
	count_cmds(shell);
	format_cmds(shell);
	if (!process_all_heredocs(shell))
	{
		unlink_heredoc();
		dup2(restore_stdout, STDOUT_FILENO);
		close(restore_stdout);
		return (0);
	}
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
	unlink_heredoc();
	return (0);
}

// TODO : les fichiers heredoc ne sont pas supprimés si interrompu avec ctrl+c
