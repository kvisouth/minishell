/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:09:05 by kevso             #+#    #+#             */
/*   Updated: 2025/04/11 02:35:31 by kevso            ###   ########.fr       */
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
	if (!arg || ft_strchr(arg, '=') == NULL)
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

int	append_str_to_env(t_shell *shell, char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = ft_strdup(shell->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	if (!new_env[i] || !new_env[i + 1])
	{
		free_tab(new_env);
		return (1);
	}
	free_tab(shell->env);
	shell->env = new_env;
	return (0);
}

int	builtin_export(t_shell *shell, t_simple_cmds *cmd)
{
	if (!check_export_args(cmd))
		return (ft_putstr_fd("incorrect format\n", 2), 1);
	if (check_export_args(cmd) == 2)
		return (0);
	printf("%s\n", cmd->str[1]);
	if (append_str_to_env(shell, cmd->str[1]))
		return (1);
	return (0);
}
