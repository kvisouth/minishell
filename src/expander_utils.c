/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:47:40 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/22 21:26:31 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Check if character is valid in a variable name */
int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

/* Find the next $VAR or $? in str, update exp positions, return name */
char	*find_next_variable(char *s, t_expand *exp)
{
	int	i;

	i = exp->start_pos;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1]
			&& (is_valid_var_char(s[i + 1], 1)
				|| s[i + 1] == '?'))
		{
			exp->start_pos = i++;
			if (s[i] == '?')
			{
				exp->end_pos = i + 1;
				return (ft_strdup("?"));
			}
			exp->end_pos = i;
			while (s[exp->end_pos]
				&& is_valid_var_char(s[exp->end_pos], 0))
				exp->end_pos++;
			return (ft_substr(s, i, exp->end_pos - i));
		}
		i++;
	}
	return (NULL);
}

/*
** Determine if we should expand at pos:
** return 0 if inside single quotes, else 1.
*/
int	should_expand_in_quotes(char *token, int pos, t_expand *exp)
{
	int	in_sq;
	int	in_dq;
	int	i;

	in_sq = 0;
	in_dq = 0;
	exp->in_quotes = 0;
	i = 0;
	while (i < pos)
	{
		if (token[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (token[i] == '"' && !in_sq)
			in_dq = !in_dq;
		i++;
	}
	if (in_sq)
		exp->in_quotes = 1;
	else if (in_dq)
		exp->in_quotes = 2;
	return (!in_sq);
}

// Add this helper function to find values in the environment
char	*get_env_value(char *name, char **env)
{
	int		i;
	size_t	name_len;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

/* Retrieve the value for a variable name (handles “?”) */
char	*expand_variable(char *var_name, char **env)
{
	char		*var_value;
	extern int	g_sig;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_sig));
	var_value = get_env_value(var_name, env);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}
