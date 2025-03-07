/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:53:04 by kevso             #+#    #+#             */
/*   Updated: 2025/03/07 16:50:53 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Just like a count_words, but ignores the spaces inside quotes */
int	count_tokens(char *str, t_lexer *lex)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	lex->quote_char = '\0';
	lex->inside_quotes = false;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (lex->inside_quotes && str[i] == lex->quote_char)
				lex->inside_quotes = false;
			else if (!lex->inside_quotes)
			{
				lex->inside_quotes = true;
				lex->quote_char = str[i];
			}
		}
		if (!lex->inside_quotes && str[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

/* Splits the cmdline into tokens from every spaces exept those inside quotes */
/* Takes the same logic than count_tokens, instead of counting, splits str.   */
char	**split_tokens(char *str, t_lexer *lex)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * (lex->token_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	lex->quote_char = '\0';
	lex->inside_quotes = false;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (lex->inside_quotes && str[i] == lex->quote_char)
				lex->inside_quotes = false;
			else if (!lex->inside_quotes)
			{
				lex->inside_quotes = true;
				lex->quote_char = str[i];
			}
		}
		if (!lex->inside_quotes && str[i] == ' ')
		{
			str[i] = '\0';
			i++;
			continue ;
		}
		if (i == 0 || str[i - 1] == '\0')
		{
			tokens[j] = &str[i];
			j++;
		}
		i++;
	}
	tokens[j] = NULL;
	return (tokens);
}
