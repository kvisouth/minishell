/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:17:21 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 14:18:16 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		handle_child_process(shell, cmd, prev_fd, NULL);
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
