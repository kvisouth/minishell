/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/03/11 13:35:17 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manual_set_variables(t_shell *shell)
{
	(void)shell;
	// set variables manually
	// for command : ls -la | wc -l > output.txt
	// shell->cmd->args = {"ls", "-la", NULL};
	return ;
}

/* Returns the exit status */
int	exec(t_shell *shell)
{
	(void)shell;
	// manual_set_variables(shell);
	// execute the command

	return (1);
}