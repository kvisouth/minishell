/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:20:31 by kevso             #+#    #+#             */
/*   Updated: 2025/02/03 15:23:55 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Checks if the env is empty */
int	is_env_empty(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i == 0)
		return (1);
	return (0);
}

/* Sets the "PWD" variable */
char	*set_env_pwd(void)
{
	char	*buffer;
	char	*pwd;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
		return (NULL);
	pwd = ft_strjoin("PWD=", buffer);
	free(buffer);
	if (!pwd)
		return (NULL);
	return (pwd);
}

/* Creates "PWD", "SHLVL" and "_" variables for empty env */
char	**create_minimal_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	env[0] = set_env_pwd();
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	if (!env[0] || !env[1] || !env[2])
		return (NULL);
	return (env);
}

/* Copies the whole envp into env */
char	**copy_envp(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

/* Creates it's own env variables if minishell is started with "env -i"
Else, it starts normally and copies the whole env */
char	**init_shell_env(char **envp)
{
	char	**env;

	env = NULL;
	if (is_env_empty(envp))
	{
		env = create_minimal_env();
		if (!env)
		{
			free_tab(env);
			return (NULL);
		}
	}
	else
	{
		env = copy_envp(envp);
		if (!env)
		{
			free_tab(env);
			return (NULL);
		}
	}
	return (env);
}
