/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/03/18 16:07:09 by abreuil          ###   ########.fr       */
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

void	count_cmds(t_shell *shell)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = shell->simple_cmds;
	while (tmp)
	{
		i++;
		tmp->index = i;
		tmp = tmp->next;
	}
	shell->nb_cmds = i;
}

/* Returns the exit status */
int	exec(t_shell *shell)
{
	count_cmds(shell);
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

