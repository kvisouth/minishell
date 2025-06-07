/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:15:58 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 22:24:02 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Happens in the child process, after command execution
- Closes the previous file descriptor (prev_fd) if it was opened before
- Closes the write end (1) of the pipe if the command (if not last) so
  that the next command can read from it.
- Resets the previous file descriptor to the read end (0) of the pipe
  if the command has a next command, otherwise sets it to -1.
*/
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

/*
The function that waits for all child processes to finish and sets the global
exit status variable `g_sig` based on the last child's exit status.
- Waits for any child process to finish
- WIFEXITED checks if the child exited normally
	if so, it sets `g_sig` to the exit status with `WEXITSTATUS`
- WIFSIGNALED checks if the child was terminated by a signal
	if so, it sets `g_sig` to 128 + the signal number with `WTERMSIG`

WEXITSTATUS : the exit status of the child process (0 for success, 1 for error..)
WTERMSIG : the signal that terminated the child process (CTRL+C would be 2..)
*/
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

/*
Fills "pipefd" array (read and write ends)
if the actual command is not the last one
*/
void	create_pipe_for_cmd(t_simple_cmds *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit(1);
	}
}

/*
Creates a child process to execute the command of the pipeline.
*/
void	fork_and_execute_cmd(t_shell *shell, t_simple_cmds *cmd,
							int prev_fd, int pipefd[2])
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(1);
	if (cmd->pid == 0)
		handle_child_process(shell, cmd, prev_fd, pipefd);
}

/*
For each command in the pipeline, this function:
1. Creates a pipe if the command (exept last)
2. Forks a child process to execute the command
3. Closes the pipe ends and resets the previous file descriptor
Then it waits for all child processes to finish.
*/
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
