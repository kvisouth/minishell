/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:19:01 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 15:46:36 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Goes in the right function based on "cmd" */
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

/* Saves stdin and stdout, and restores them after executing the builtin */
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
