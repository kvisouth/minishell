/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:55:17 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/18 16:55:23 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *remove_quotes(char *str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	*result;
	char	quote;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote = '\0';
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote = str[i];
			i++;
		}
		else if (str[i] == quote && in_quotes)
		{
			in_quotes = 0;
			quote = '\0';
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}