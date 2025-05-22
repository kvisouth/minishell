/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:22:28 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/22 21:24:40 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Replace the next occurrence in token with exp->var_value */
char	*replace_variable(char *token, t_expand *exp)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
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
	tmp = ft_strjoin(prefix, exp->var_value);
	free(prefix);
	if (!tmp)
	{
		free(suffix);
		return (NULL);
	}
	result = ft_strjoin(tmp, suffix);
	free(tmp);
	free(suffix);
	return (result);
}
