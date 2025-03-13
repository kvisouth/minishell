/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_add_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:57:34 by kevso             #+#    #+#             */
/*   Updated: 2025/03/13 16:58:00 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(t_shell *shell)
{
	int		i;
	char	*path;

	i = 0;
	if (!shell->env)
		return (NULL);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(shell->env[i] + 5);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

/* Concatenates "/" to each directory (/usr/bin -> /usr/bin/) */
char	**concat_slash_to_dirs(char **dirs)
{
	int		i;
	char	*tmp;
	char	**new_dirs;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		free(dirs[i]);
		dirs[i] = tmp;
		i++;
	}
	new_dirs = ft_calloc(i + 1, sizeof(char *));
	if (!new_dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		new_dirs[i] = dirs[i];
		i++;
	}
	free(dirs);
	return (new_dirs);
}

/* Concatenates the cmd to each directory (/usr/bin/ -> /usr/bin/ls) */
char	**concat_cmd_to_dirs(char *cmd, char **dirs)
{
	int		i;
	char	*tmp;
	char	*command;
	char	**new_dirs;

	command = ft_substr(cmd, 0, ft_strchr(cmd, ' ') - cmd);
	if (!command)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], command);
		if (!tmp)
			return (free(command), NULL);
		free(dirs[i]);
		dirs[i] = tmp;
		i++;
	}
	new_dirs = ft_calloc(i + 1, sizeof(char *));
	if (!new_dirs)
		return (free(command), NULL);
	i = -1;
	while (dirs[++i])
		new_dirs[i] = dirs[i];
	return (free(dirs), free(command), new_dirs);
}

/* Returns the path of the command if it exists */
/* If the command does not exist, returns the first dir */
char	*choose_path_in_dirs(char **dirs)
{
	int		i;
	char	*cmd;

	i = 0;
	while (dirs[i])
	{
		if (access(dirs[i], F_OK) == 0)
		{
			cmd = ft_strdup(dirs[i]);
			if (!cmd)
				return (NULL);
			free(dirs);
			return (cmd);
		}
		i++;
	}
	cmd = ft_strdup(dirs[0]);
	if (!cmd)
		return (NULL);
	free(dirs);
	return (cmd);
}

/* Edits simple_cmds->str[0] to the full path */
/* From "ls" to "/usr/bin/ls" */
int	add_path_to_cmd(t_shell *shell)
{
	char	*cmd;
	char	**dirs;

	shell->path = get_path(shell);
	if (!shell->path)
		return (0);
	cmd = shell->simple_cmds->str[0]; // cmd = ls
	dirs = ft_split(shell->path, ':'); // dirs = ["/usr/bin", "/bin", ...]
	if (!dirs)
		return (0);
	dirs = concat_slash_to_dirs(dirs); // dirs = ["/usr/bin/", "/bin/", ...]
	if (!dirs)
		return (0);
	dirs = concat_cmd_to_dirs(cmd, dirs); // dirs = ["/usr/bin/ls", "/bin/ls", ...]
	if (!dirs)
		return (0);
	cmd = choose_path_in_dirs(dirs); // cmd = "/usr/bin/ls"
	if (!cmd)
		return (0);
	return (1);
}
