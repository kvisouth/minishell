/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:09:05 by kevso             #+#    #+#             */
/*   Updated: 2025/03/28 15:27:07 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Checks if the argument is in the format : foo=bar or foo or foo=
*/
int	check_export_args(t_simple_cmds *cmd)
{
	char	*arg;
	int		i;

	arg = cmd->str[1];
	if (!arg)
		return (2);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	if (arg[i] == '=')
	{
		i++;
		while (arg[i])
		{
			if (!ft_isprint(arg[i]) && arg[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	builtin_export(t_shell *shell, t_simple_cmds *cmd)
{
	// char	*new;

	// new = NULL;
	if (!check_export_args(cmd))
		return (ft_putstr_fd("incorrect format\n", 2), 1);
	if (check_export_args(cmd) == 2)
	{
		print_env_sorted(shell->env);
		return (0);
	}
	return (0);
}
