/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:53:04 by kevso             #+#    #+#             */
/*   Updated: 2025/06/09 11:58:10 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Updates the quote status */
void	update_quote_status(t_lexer *lex, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (lex->inside_quotes && c == lex->quote_char)
			lex->inside_quotes = false;
		else if (!lex->inside_quotes)
		{
			lex->inside_quotes = true;
			lex->quote_char = c;
		}
	}
}

/* Just like a count_words, but ignores the spaces inside quotes */
int	count_tokens_core(char *str, t_lexer *lex)
{
	int		i;
	int		count;
	bool	in_token;

	i = 0;
	count = 0;
	in_token = false;
	while (str[i])
	{
		update_quote_status(lex, str[i]);
		if (!lex->inside_quotes && str[i] == ' ')
		{
			if (in_token)
			{
				count++;
				in_token = false;
			}
		}
		else
			in_token = true;
		i++;
	}
	if (in_token)
		count++;
	return (count);
}

int	count_tokens(char *str, t_lexer *lex)
{
	lex->quote_char = '\0';
	lex->inside_quotes = false;
	return (count_tokens_core(str, lex));
}

void	init_i_j_for_norm(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

/* Splits the cmdline into tokens from every spaces exept those inside quotes */
/* Takes the same logic than count_tokens, instead of counting, splits str.   */
char	**split_tokens(char *str, t_lexer *lex)
{
	char	**tokens;
	int		i;
	int		j;
	int		start;

	tokens = malloc(sizeof(char *) * (lex->token_count + 1));
	if (!tokens)
		return (NULL);
	init_i_j_for_norm(&i, &j);
	lex->quote_char = '\0';
	lex->inside_quotes = false;
	while (str[i])
	{
		while (str[i] && ((str[i] == ' ' || str[i] == '\t')
				&& !lex->inside_quotes))
			i++;
		start = i;
		while (str[i] && (lex->inside_quotes
				|| (str[i] != ' ' && str[i] != '\t')))
			update_quote_status(lex, str[i++]);
		if (i > start)
			tokens[j++] = ft_substr(str, start, i - start);
	}
	tokens[j] = NULL;
	return (tokens);
}
