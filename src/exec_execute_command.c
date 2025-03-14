/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:59:26 by kevso             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/14 15:13:25 by abreuil          ###   ########.fr       */
=======
/*   Updated: 2025/03/14 16:13:56 by kevso            ###   ########.fr       */
>>>>>>> 7a8817414ddda6a79c085cf934d168a0b59db229
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

<<<<<<< HEAD
//void	child_process(t_shell *shell)
//{
	
//}
=======
void	child_process(t_shell *shell, t_simple_cmds *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(1);
	}
	// char *test[] = {"w/bin/ls", "-l", NULL};
	if (cmd->pid == 0)
	{
		for (int i = 0; cmd->str[i]; i++)
			printf("cmd[%d]: %s\n", i, cmd->str[i]);
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}
>>>>>>> 7a8817414ddda6a79c085cf934d168a0b59db229

/* Executes the command */
int	execute_command(t_shell *shell)
{
	t_simple_cmds	*cmd;

	cmd = shell->simple_cmds;
	if (!shell->simple_cmds->builtin)
	{
		child_process(shell, cmd);
	}
	return (0);
}
