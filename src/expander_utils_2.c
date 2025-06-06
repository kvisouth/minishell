/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:55:17 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/19 14:28:53 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static void	process_quote(char *s, int *i, int *in_quotes, char *quote_char)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*quote_char = s[*i];
	}
	else
	{
		*in_quotes = 0;
		*quote_char = '\0';
	}
	(*i)++;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	*result;
	char	quote;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote = '\0';
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]) && !in_quotes)
			process_quote(str, &i, &in_quotes, &quote);
		else if (str[i] == quote && in_quotes)
			process_quote(str, &i, &in_quotes, &quote);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
