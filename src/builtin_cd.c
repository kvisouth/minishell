/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:40 by kevso             #+#    #+#             */
/*   Updated: 2025/04/10 14:27:31 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_env(t_shell *shell, char *tmp)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_substr(tmp, 0, ft_strchr(tmp, '=') - tmp);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, ft_strlen(str)))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(tmp);
			break ;
		}
		i++;
	}
	free(str);
}

void	update_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	update_env(shell, tmp);
	free(tmp);
}

void	update_pwd(t_shell *shell, char *cwd)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", cwd);
	update_env(shell, tmp);
	free(tmp);
}

int	count_cd_args(t_simple_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[i])
		i++;
	return (i);
}

int	builtin_cd(t_shell *shell, t_simple_cmds *cmd)
{
	char	cwd[1024];
	char	oldpwd[1024];

	getcwd(oldpwd, sizeof(oldpwd));
	if (count_cd_args(cmd) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->str[1] == NULL || cmd->str[2] != NULL)
		return (1);
	if (chdir(cmd->str[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		update_oldpwd(shell, oldpwd);
		update_pwd(shell, cwd);
	}
	return (0);
}
