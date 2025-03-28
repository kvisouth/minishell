/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:47:40 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/18 17:20:58 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Check if character is valid for a variable name*/
int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

/* Find the next variable in a string */
char	*find_next_variable(char *str, t_expand *exp)
{
	int		i;

	i = exp->start_pos;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (is_valid_var_char(str[i + 1], 1) || str[i + 1] == '?'))
		{
			exp->start_pos = i;
			i++;
			if (str[i] == '?')
			{
				exp->end_pos = i + 1;
				return (ft_strdup("?"));
			}
			exp->end_pos = i;
			while (str[exp->end_pos] && is_valid_var_char(str[exp->end_pos], 0))
				(exp->end_pos)++;
			return (ft_substr(str, i, exp->end_pos - i));
			}
		i++;
	}
	return (NULL);	
}

/* handle quotes while expanding variables */
int	should_expand_in_quotes(char *token, int pos, t_expand *exp)
{
	int i;
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    
    i = 0;
    exp->in_quotes = 0;
    while (i < pos)
    {
        if (token[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (token[i] == '\"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        i++;
    }
    if (in_single_quotes)
        exp->in_quotes = 1;
    else if (in_double_quotes)
        exp->in_quotes = 2;
    else
        exp->in_quotes = 0;
    return !in_single_quotes;
}

char	*expand_variable(char *var_name)
{
	char *var_value;
	extern int g_sig;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_sig));
	var_value = getenv(var_name);
	if (!var_value)
		return (ft_strdup(""));
		
	return (ft_strdup(var_value));
}

/* replace a variable in a token with its value */
char	*replace_variable(char *token, t_expand *exp)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;
	
	prefix = ft_substr(token, 0, exp->start_pos);
	if (!prefix)
		return (NULL);
	suffix = ft_strdup(token + exp->end_pos);
	if (!suffix)
	{
		free(prefix);
		return (NULL);
	}
	temp = ft_strjoin(prefix, exp->var_value);
	free(prefix);
	if (!temp)
	{
		free(suffix);
		return (NULL);
	}
	result = ft_strjoin(temp, suffix);
	free(temp);
	free(suffix);
	return (result);
}