/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:59:26 by kevso             #+#    #+#             */
/*   Updated: 2025/03/18 15:26:44 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	child_process(t_shell *shell, t_simple_cmds *cmd)
// {
// 	cmd->pid = fork();
// 	if (cmd->pid == -1)
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	if (cmd->pid == 0)
// 	{
// 		for (int i = 0; cmd->str[i]; i++)
// 			printf("cmd[%d]: %s\n", i, cmd->str[i]);
// 		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
// 		{
// 			perror("execve");
// 			exit(1);
// 		}
// 	}
// }

// /* Executes the command */
// int	execute_command(t_shell *shell)
// {
// 	t_simple_cmds	*cmd;

// 	cmd = shell->simple_cmds;
// 	if (!shell->simple_cmds->builtin)
// 	{
// 		child_process(shell, cmd);
// 	}
// 	return (0);
// }
