/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/03/14 16:38:12 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Returns 1 if the command does not have a path */
int	cmd_have_no_path(char *cmd)
{
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.') || ft_strchr(cmd, '~'))
		return (0);
	return (1);
}


/* Returns the exit status */
int	exec(t_shell *shell)
{
	while (shell->simple_cmds)
	{
		if (shell->simple_cmds->builtin == false)
		{
			if (cmd_have_no_path(shell->simple_cmds->str[0]))
			{
				if (!add_path_to_cmd(shell))
					return (0);
			}
		}
		execute_command(shell);
		shell->simple_cmds = shell->simple_cmds->next;
	}
	wait(NULL);
	return (0);
}
