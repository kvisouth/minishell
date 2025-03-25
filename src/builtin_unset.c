/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:15:14 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/25 15:55:02 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int	is_matching_var(char *env_entry, char *var_name)
{
	int	name_len;
	
	name_len = ft_strlen(var_name);
	return (!ft_strncmp(env_entry, var_name, name_len) && env_entry[name_len] == '=');
}

int	builtin_unset(t_shell *shell, t_simple_cmds *cmd)
{
	int		i;
	int		env_index;
	char	*var_name;

	i = 1;
	while(cmd->str[i])
	{
		var_name = cmd->str[i];
		env_index = 0;
		while (shell->env[env_index])
		{
			if (is_matching_var(shell->env[env_index], var_name))
			{
				free(shell->env[env_index]);
				while (shell->env[env_index + 1])
				{
					shell->env[env_index] = shell->env[env_index + 1];
					env_index++;
				}
				shell->env[env_index] = NULL;
				break;
			}
			env_index++;
		}
		i++;
	}
	return 0;
}