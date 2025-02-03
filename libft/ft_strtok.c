/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:24:31 by kevisout          #+#    #+#             */
/*   Updated: 2025/01/10 13:24:54 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*ptr;
	char		*ret;
	int			i;

	if (str)
		ptr = str;
	if (!ptr || !*ptr)
		return (NULL);
	ret = ptr;
	i = 0;
	while (ptr[i])
	{
		if (ft_strchr(delim, ptr[i]))
		{
			ptr[i++] = '\0';
			break ;
		}
		i++;
	}
	ptr += i;
	return (ret);
}
