/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:15:58 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 14:16:52 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_and_reset_pipes(int *prev_fd, int pipefd[2], t_simple_cmds *cmd)
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
		handle_child_process(shell, cmd, prev_fd, pipefd);
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
		create_pipe_for_cmd(cmd, pipefd);
		fork_and_execute_cmd(shell, cmd, prev_fd, pipefd);
		close_and_reset_pipes(&prev_fd, pipefd, cmd);
		if (!cmd->next)
			last_pid = cmd->pid;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
	reset_signals_for_parent();
}
