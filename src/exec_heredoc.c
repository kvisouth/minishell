/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:42 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 23:00:08 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Storing fd in a static to be able to close it on SIGINT (getter/setter) */
static int	heredoc_fd_manager(int set, int value)
{
	static int	fd = -1;

	if (set)
		fd = value;
	return (fd);
}

/* Closes the fd and exits with status 130 on SIGINT */
void	heredoc_sigint_handler(int sig)
{
	int	fd;

	fd = heredoc_fd_manager(0, 0);
	if (fd != -1)
		close(fd);
	g_sig = 130;
	exit(g_sig);
	(void)sig;
}

/* Exits the loop when the delimiter is found */
void	child_process_heredoc(char *delimiter, char *filename, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*expanded;

	signal(SIGINT, heredoc_sigint_handler);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	heredoc_fd_manager(1, fd);
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
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	close(fd);
	exit(0);
}

/*
WIFSIGNALED checks if the child process was terminated by a signal
*/
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
	shell->heredoc_flag = 1;
	return (1);
}

/* Loops to process all heredocs in every commands */
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
