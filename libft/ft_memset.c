/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:35:03 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 12:28:02 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_memset remplie les 'n' premiers octets dans la zone memoire pointee par 's'
avec le caractere 'c'. Utilisable dans ft_bzero ou ft_calloc par exemple.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
		str[i++] = (char)c;
	return (s);
}
