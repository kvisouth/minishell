/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:23 by kevso             #+#    #+#             */
/*   Updated: 2025/02/03 17:10:01 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell(t_shell *shelL)
{
	
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1 && av)
		return (1);
	shell.env = NULL;
	shell.env = init_shell_env(envp);
	if (!shell.env)
		return (1);
	minishell(&shell);
	return (0);
}
