/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/07 14:49:36 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isoperator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

char	*add_spaces_to_cmdline(char *cmdline, t_lexer *lex)
{
	char	quote_char;
	int		i;
	int		j;

	lex->new_cmdline = ft_calloc(ft_strlen(cmdline) * 3 + 1, sizeof(char));
	if (!lex->new_cmdline)
		return (NULL);
	i = 0;
	j = 0;
	lex->inside_quotes = false;
	quote_char = '\0';
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '\"')
		{
			if (lex->inside_quotes && cmdline[i] == quote_char)
			{
				lex->inside_quotes = false;
				quote_char = '\0';
			}
			else if (!lex->inside_quotes)
			{
				lex->inside_quotes = true;
				quote_char = cmdline[i];
			}
			lex->new_cmdline[j++] = cmdline[i++];
		}
		if (!lex->inside_quotes && ft_isoperator(cmdline[i]))
		{
			if (i > 0 && cmdline[i - 1] != ' ' && !ft_isoperator(cmdline[i - 1]))
				lex->new_cmdline[j++] = ' ';
			while (cmdline[i] && ft_isoperator(cmdline[i]))
				lex->new_cmdline[j++] = cmdline[i++];
			if (cmdline[i] && cmdline[i] != ' ')
				lex->new_cmdline[j++] = ' ';
		}
		else
			lex->new_cmdline[j++] = cmdline[i++];
	}
	lex->new_cmdline[j] = '\0';
	return (lex->new_cmdline);
}

int	lexer(t_lexer *lex, char *cmdline)
{
	char	*new_cmdline;

	new_cmdline = add_spaces_to_cmdline(cmdline, lex);
	if (!new_cmdline)
		return (0);
	printf("lex->new_cmdline: %s\n", lex->new_cmdline);
	return (1);
	(void)lex;
	(void)cmdline;
}
