/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:31:57 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 14:32:01 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	end(int code, bool kill, char *msg)
{
	g_sig = code;
	if (kill == TRUE)
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		else
			perror("Error");
		exit(code);
	}
	else
	{
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
		else
			perror("Error");
	}
}

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

/* Append the path to every non-builtin command */
void	format_cmds(t_shell *shell)
{
	t_simple_cmds	*cmd;

	cmd = shell->simple_cmds;
	while (cmd)
	{
		if (!cmd->str[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->builtin == false)
		{
			if (cmd_have_no_path(cmd->str[0]))
			{
				if (!add_path_to_cmd(shell, cmd))
					return ;
			}
		}
		cmd = cmd->next;
	}
}
