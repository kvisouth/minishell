/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nok <nok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:09:05 by kevso             #+#    #+#             */
/*   Updated: 2025/04/12 09:45:37 by nok              ###   ########.fr       */
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

/*
Checks if the variable already exists in the environment
1 : variable already exists
0 : variable doesn't exist
*/
int	check_var_already_exist(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var,
				ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
Deletes the line of 'var' from the environment
Returns the new environment without that variable
*/
int	delete_var_env(t_shell *shell, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var,
				ft_strchr(shell->env[i], '=') - shell->env[i]) != 0)
			new_env[j++] = shell->env[i];
		i++;
	}
	new_env[j] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

/*
Adds the variable 'var' to the environment
Returns the new environment with that variable
*/
int	add_var_env(t_shell *shell, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

int	builtin_export(t_shell *shell, t_simple_cmds *cmd)
{
	if (!check_export_args(cmd))
		return (ft_putstr_fd("incorrect format\n", 2), 1);
	if (check_export_args(cmd) == 2)
		return (0);
	if (check_var_already_exist(shell, cmd->str[1]))
	{
		if (!delete_var_env(shell, cmd->str[1]))
			return (ft_putstr_fd("malloc error\n", 2), 1);
		if (!add_var_env(shell, cmd->str[1]))
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else
	{
		if (!add_var_env(shell, cmd->str[1]))
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	return (0);
}
