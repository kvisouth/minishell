/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/07 15:51:52 by kevso            ###   ########.fr       */
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
		if (!lex->inside_quotes && (i == 0 || str[i - 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

/* Splits the cmdline into tokens */

int	lexer(t_shell *shell)
{
	shell->new_cmdline = add_spaces_to_cmdline(shell->cmdline, &shell->lexer);
	if (!shell->new_cmdline)
		return (0);
	// printf("new_cmdline: %s\n", shell->new_cmdline);
	shell->lexer.token_count = count_tokens(shell->new_cmdline, &shell->lexer);
	// printf("token_count: %d\n", shell->lexer.token_count);
	shell->lexer.tokens = split_tokens(shell->new_cmdline, &shell->lexer);
	if (!shell->lexer.tokens)
		return (0);
	return (1);
}
