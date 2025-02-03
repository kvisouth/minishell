/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:12:07 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/04 22:18:36 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strdup duplique 's'. Dans quoi ?
Dans un autre const char qu'on doit egalement malloc
*/
char	*ft_strdup(const char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i])
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
