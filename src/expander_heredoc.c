/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:27:34 by kevisout          #+#    #+#             */
/*   Updated: 2025/05/23 15:50:50 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** Returns 1 always except when in double quotes
*/
int	should_expand_in_heredoc(char *token, int pos, t_expand *exp)
{
	int	in_dq;
	int	i;

	in_dq = 0;
	exp->in_quotes = 0;
	i = 0;
	while (i < pos)
	{
		if (token[i] == '"')
			in_dq = !in_dq;
		i++;
	}
	if (in_dq)
		exp->in_quotes = 2;
	return (1);
}

static char	*process_heredoc_var(char *expanded, t_expand *exp, char **env)
{
	exp->var_value = expand_variable(exp->var_name, env);
	free(exp->var_name);
	if (!exp->var_value)
		return (NULL);
	exp->expanded = replace_variable(expanded, exp);
	free(exp->var_value);
	free(expanded);
	if (!exp->expanded)
		return (NULL);
	return (exp->expanded);
}

/*
**  Expand all variables in a heredoc line.
*/
char	*expand_heredoc_line(char *line, char **env)
{
	char		*expanded;
	t_expand	exp;

	init_expand(&exp);
	expanded = ft_strdup(line);
	if (!expanded)
		return (NULL);
	exp.var_name = find_next_variable(expanded, &exp);
	while (exp.var_name)
	{
		if (!should_expand_in_heredoc(expanded, exp.start_pos, &exp))
		{
			free(exp.var_name);
			exp.start_pos = exp.end_pos;
		}
		else
		{
			expanded = process_heredoc_var(expanded, &exp, env);
			if (!expanded)
				return (NULL);
		}
		exp.var_name = find_next_variable(expanded, &exp);
	}
	return (expanded);
}
