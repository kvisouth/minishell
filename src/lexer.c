/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/02/11 16:10:44 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Return the nb of tokens in the string (skip the quotes) */
int	count_tokens(char *str, char *sep)
{
	bool	in_quote;
	int		count;
	int		i;

	in_quote = false;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == false)
				in_quote = true;
			else
				in_quote = false;
		}
		if (in_quote == false && ft_strchr(sep, str[i]))
			count++;
		i++;
	}
	return (count + 1);
}

/*
Splits the string into a char ** array of tokens, based on separators.
It ignores separators if it is between double or single quotes.
*/
char	**tokenize(char *str, char *sep)
{
	bool	in_quote;
	char	**tokens;
	int		i;
	int		j;

	in_quote = false;
	tokens = ft_calloc(count_tokens(str, sep) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == false)
				in_quote = true;
			else
				in_quote = false;
		}
		if (in_quote == false && ft_strchr(sep, str[i]))
		{
			tokens[j] = ft_substr(str, 0, i);
			if (!tokens[j])
				return (NULL);
			str += i + 1;
			i = 0;
			j++;
		}
		i++;
	}
	tokens[j] = ft_strdup(str);
	if (!tokens[j])
		return (NULL);
	return (tokens);
}

/*
Lexer will "tokenize" the input string into a list of tokens.

minshell> grep if < main.c | cat -e > output.txt
will be tokenized into:
["grep", "if", "<", "main.c", "|", "cat", "-e", ">", "output.txt"]
*/
int	lexer(t_lexer *lex, char *cmdline)
{
	lex->token_count = count_tokens(cmdline, " \t\n\r\a");
	printf("Token count: %d\n", lex->token_count);
	lex->tokens = tokenize(cmdline, " \t\n\r\a");
	if (!lex->tokens)
		return (0);
	for (int i = 0; i < lex->token_count; i++)
		printf("Token %d: %s\n", i, lex->tokens[i]);
	return (1);
}