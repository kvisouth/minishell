/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:46:29 by kevso             #+#    #+#             */
/*   Updated: 2025/05/09 17:56:50 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
Multiple arguments : no exit, g_sig = 1
argument not a number : exit, g_sig = 2
argument over 255 : exit, argument % 256
argument negative : exit, argument + 256
*/
void	builtin_exit(char **arg)
{
	int		exit_code;

	exit_code = g_sig;
	if (arg[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_sig = 1;
		return ;
	}
	if (arg[1])
	{
		if (!check_exit_arg(arg[1]))
		{
			g_sig = 2;
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(g_sig);
		}
		else
		{
			exit_code = ft_atoi(arg[1]) % 256;
			if (exit_code < 0)
				exit_code += 256;
		}
	}
	exit(exit_code);
}
