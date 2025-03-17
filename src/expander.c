/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:52:52 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/17 16:03:20 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_expand(t_expand *exp)
{
	exp->start_pos = 0;
	exp->end_pos = 0;
	exp->in_quotes = 0;
	exp->expanded = NULL;
	exp->var_name = NULL;
	exp->var_value = NULL;
}

/* Expand environment variables in all tokens */
int	expand_tokens(t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (i < shell->lexer.token_count)
	{
		expanded = expand_token(shell->lexer.tokens[i]);
		if (!expanded)
			return (0);
		free(shell->lexer.tokens[i]);
		shell->lexer.tokens[i] = expanded;
		i++;
	}
	return (1);
}

char	*expand_token(char *token)
{
	char 	*expanded;
	t_expand exp;

	init_expand(&exp);
	expanded = ft_strdup(token);
	if (!expanded)
		return (NULL);
	while ((exp.var_name = find_next_variable(expanded, &exp)))
	{
		if (!should_expand_in_quotes(expanded, exp.start_pos, &exp))
		{
			free(exp.var_name);
			continue ;
		}
		exp.var_value = expand_variable(exp.var_name);
		free(exp.var_name);
		if (!exp.var_value)
		{
			free(exp.var_name);
			free(expanded);
			return (NULL);
		}
		exp.expanded = replace_variable(expanded, &exp);
		free(exp.var_value);
		free(expanded);
		if (!exp.expanded)
			return (NULL);
		expanded = exp.expanded;
	}
	return (expanded);
}