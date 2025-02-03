/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:46:18 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/12 16:23:24 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strchr retourne un pointeur sur la premiere occurence de 'c' dans 's'
retourne NULL si 'c' n'est pas trouvee dans 's'.
Cas specifique : si c = '\0', un pointeur vers le caractere NULL de 's'
sera retournee (la fin donc)
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
