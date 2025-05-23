/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:34:54 by kevso             #+#    #+#             */
/*   Updated: 2025/05/23 17:13:24 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_for_n_flag(char **args, int *index)
{
	int		i;
	int		j;
	bool	found;

	i = 1;
	found = false;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
				break ;
			found = true;
		}
		else
			break ;
		i++;
	}
	*index = i;
	return (found);
}

int	builtin_echo(char **args)
{
	bool	n_flag;
	int		i;

	n_flag = check_for_n_flag(args, &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
