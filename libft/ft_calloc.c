/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:00:35 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/12 14:02:21 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_calloc alloue (nmemb * size) octets avec malloc().
Cet espace est rempli de 0. La ou malloc ne rempli rien.

Si la multiplication de (nmemb * size) depasse INT_MAX
alors ft_calloc retourne une erreur (NULL).

On cast un (void *) en (char *) car c'est pour indiquer qu'on veut
acceder a la memoire (celle pointee par void*) octet par octet.
Et pour indiquer ca, il faut cast un char, qui est typiquement 1 octet.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	i;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		((char *)ret)[i++] = 0;
	return (ret);
}
