/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:00:22 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 12:27:39 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_memchr scan les 'n' premiers octets pointee par 's'
Il cherche la premiere occurence du caractere 'c' dans cette zone scannee.
Retourne un pointeur sur cet occurence si trouvee ou NULL s'il n'est pas trv.
'c' et 's' sont interpretees par des unsigned char.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
