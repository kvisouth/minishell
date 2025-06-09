/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:58:12 by kevso             #+#    #+#             */
/*   Updated: 2025/06/09 11:44:28 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_op(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

/* Ignores everything inside quotes */
void	handle_quotes(char *cmdline, t_lexer *lex, int *i, int *j)
{
	if (cmdline[*i] == '\'' || cmdline[*i] == '\"')
	{
		if (lex->inside_quotes && cmdline[*i] == lex->quote_char)
		{
			lex->inside_quotes = false;
			lex->quote_char = '\0';
		}
		else if (!lex->inside_quotes)
		{
			lex->inside_quotes = true;
			lex->quote_char = cmdline[*i];
		}
		lex->new_cmdline[(*j)++] = cmdline[(*i)++];
	}
}

/*
Copy cmdline into new_cmdline while inserting spaces before and after op's
1. check if last char is not space & last char is not op
   if so : insert a space before the op
2. while current char is op, copy it to new_cmdline
3. checks if next char is not space
   if so : insert a space after the op
4. else : copy.
*/
void	handle_operators(char *cmdline, t_lexer *lex, int *i, int *j)
{
	if (!lex->inside_quotes && is_op(cmdline[*i]))
	{
		if (*i > 0 && cmdline[*i - 1] != ' ' && !is_op(cmdline[*i - 1]))
			lex->new_cmdline[(*j)++] = ' ';
		while (cmdline[*i] && is_op(cmdline[*i]))
			lex->new_cmdline[(*j)++] = cmdline[(*i)++];
		if (cmdline[*i] && cmdline[*i] != ' ')
			lex->new_cmdline[(*j)++] = ' ';
	}
	else
		lex->new_cmdline[(*j)++] = cmdline[(*i)++];
}

/* Ignore quotes, and copy cmdline to new_cmdline, inserting spaces*/
char	*add_spaces_to_cmdline(char *cmdline, t_lexer *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	lex->new_cmdline = ft_calloc(ft_strlen(cmdline) * 3 + 1, sizeof(char));
	if (!lex->new_cmdline)
		return (NULL);
	lex->inside_quotes = false;
	lex->quote_char = '\0';
	while (cmdline[i])
	{
		handle_operators(cmdline, lex, &i, &j);
		handle_quotes(cmdline, lex, &i, &j);
	}
	lex->new_cmdline[j] = '\0';
	return (lex->new_cmdline);
}
