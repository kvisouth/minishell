/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:01:45 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 12:27:57 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_memmove c'est le frere de ft_memcpy, sauf que lui, gere les zones memoires
dest et src qui se chevauchent, la ou ft_memcpy ne veut absolument pas que ces
zones se chevauchent.

Pour verifier le chevauchement, on a notre condition IF compare la position
relative de dest et src dans la memoire. On verifie si l'adresse 'd' est
situee apres l'adresse 's' dans la memoire.

Dans le cas ou d > s, la destination se trouve APRES la source, donc si on
copie d'une maniere classique de gauche a droite, on risque de copier des
donnees qui on deja ete ecrasees par le debut de al copie, car d et s 
se chevauchent.
C'est pour ca qu'on copie de droite a gauche.

Sinon, dans la condition ELSE, c'est le cas ou ils ne chevauchent pas,
et donc on peut reprendre le raisonnement de ft_memcpy.
Donc une copie de gauche a droite.
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if ((char *)dest > (const char *)src)
	{
		while (n > 0)
		{
			((char *)dest)[n - 1] = ((const char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*
Au debut j'avais des variables qui etaient des cast de dest et src
pour que ce soit plus lisible mais a cause de la norme j'ai enlever ca
et c'est illisible
*/
