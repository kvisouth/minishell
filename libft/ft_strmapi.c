/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:01:19 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/11 16:22:51 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strmapi applique la fonction 'f' a tout les caracteres des la string 's'.
Ces applications se font dans une nouvelle chaine a malloc et a retourner.

Ici, 'f' retourne un caractere et prend un caractere, qui peut etre le caract.
actuel, et prend un unsigned int qui peut etre l'indice.
Donc on note (ligne 39) : ret[i] = (*f)(i , s[i]);
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = (*f)(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
