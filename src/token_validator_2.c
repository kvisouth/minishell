/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validator_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:29:45 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/11 15:33:39 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_consecutive_ops(char *curr_token, char *next_token)
{
    if (next_token && is_operator(curr_token) && is_operator(next_token))
	{
		if ((ft_strcmp(curr_token, "<") == 0 && ft_strcmp(next_token, "<") == 0) ||
			(ft_strcmp(curr_token, ">") == 0 && ft_strcmp(next_token, ">") == 0))
		{
			return (1);
		}
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(next_token, 2);
        ft_putstr_fd("'\n", 2);
        return (0);
	}
    return (1);
}