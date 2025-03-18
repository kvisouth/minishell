/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:39:40 by kevso             #+#    #+#             */
/*   Updated: 2025/03/18 16:12:06 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cd with only a relative or absolute path
int	builtin_cd(t_shell *shell, t_simple_cmds *cmd)
{
	// char	cwd[1024];
	char	oldpwd[1024];

	getcwd(oldpwd, sizeof(oldpwd));
	(void)cmd;
	(void)shell;
	return (0);
}
