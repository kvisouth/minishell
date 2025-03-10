/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:11:05 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/10 17:57:48 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Checks if token is a redirection symbol */
int	is_redirection(char *token)
{
	if (!token)
		return (0);
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || 
			!ft_strcmp(token, "<<") || !ft_strcmp(token, ">>"));
}

/* Checks if token is a pipe symbol */
int	is_pipe(char *token)
{
	if (!token)
		return (0);
	return (!ft_strcmp(token, "|"));
}

/* Checks if a token is a valid operator (pipe or redirection) */
int	is_operator(char *token)
{
	return (is_pipe(token) || is_redirection(token));
}

/* Helper function to compare strings (you may already have this in libft) */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
int	validate_tokens_for_parser(t_shell *shell)
{
	if (!validate_tokens(shell))
		return (0);
	return (1);
}