/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:52:52 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/18 14:47:55 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_expand(t_expand *exp)
{
	exp->start_pos = 0;
	exp->end_pos = 0;
	exp->in_quotes = 0;
	exp->expanded = NULL;
	exp->var_name = NULL;
	exp->var_value = NULL;
}

/* Expand environment variables in all tokens */
static char	*replace_next_variable(char *expanded, t_expand *exp)
{
	char	*value;

	exp->var_value = expand_variable(exp->var_name);
	free(exp->var_name);
	if (!exp->var_value)
		return (NULL);
	exp->expanded = replace_variable(expanded, exp);
	free(exp->var_value);
	free(expanded);
	return (exp->expanded);
}

/*
**  Expand all variables in a single token.
*/
char	*expand_token(char *token)
{
	char		*expanded;
	t_expand	exp;

	init_expand(&exp);
	expanded = ft_strdup(token);
	if (!expanded)
		return (NULL);
	exp.var_name = find_next_variable(expanded, &exp);
	while (exp.var_name)
	{
		if (!should_expand_in_quotes(expanded, exp.start_pos, &exp))
		{
			free(exp.var_name);
			exp.start_pos = exp.end_pos;
		}
		else
		{
			expanded = replace_next_variable(expanded, &exp);
			if (!expanded)
				return (NULL);
		}
		exp.var_name = find_next_variable(expanded, &exp);
	}
	return (expanded);
}

/*
**  Run expand_token() on every lexer token, remove quotes where needed.
*/
int	expand_tokens(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*unquoted;

	i = 0;
	while (i < shell->lexer.token_count)
	{
		tmp = expand_token(shell->lexer.tokens[i]);
		if (!tmp)
			return (0);
		if (!is_redirection(shell->lexer.tokens[i]))
		{
			unquoted = remove_quotes(tmp);
			free(tmp);
			if (!unquoted)
				return (0);
			tmp = unquoted;
		}
		free(shell->lexer.tokens[i]);
		shell->lexer.tokens[i++] = tmp;
	}
	return (1);
}
