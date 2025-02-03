/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:56:01 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 12:24:39 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strlcpy un peu comme ft_strlcat, est dite plus safe que les autres.
Il copie src dans dest, de 0 jusqu'a size - 1, pour laisser une place a '\0'
Il retourne la longueur de la string qu'il a essaye de creer.
(la longueur de src en gros)

*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && size > 1)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dest[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}
