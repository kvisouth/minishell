/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:43:03 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 12:27:52 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_memcpy va copier les 'n' premiers octets de la zone 'src' dans la zone 'dest'
Les zones memoires ne doivent pas se chevaucher ! On doit utiliser memmove sinon
La valeur de retour est un pointeur sur dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destination;
	const char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	destination = (char *)dest;
	source = (const char *)src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
