/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/03/11 13:25:59 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manual_set_variables(t_shell *shell)
{
	(void)shell;
	shell->cmd->args = malloc(3 * sizeof(char *));
	shell->cmd->args[0] = "ls";
	shell->cmd->args[1] = "-la";
	shell->cmd->args[2] = NULL;
}

/* Returns the exit status */
int	exec(t_shell *shell)
{
	(void)shell;
	manual_set_variables(shell);
	return (1);
}