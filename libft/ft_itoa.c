/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:55:01 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/12 14:05:53 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Cette fonction nous sers a connaitre la taille a malloc pour notre nombre.
Renvoie 5 si nb = -4234
Renvoie 3 si nb = 102
*/
int	get_nbr_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

/*
ft_itoa transforme un int (n) en sa representation en chaine de caracteres.
1 - i = la longueur a malloc (longueur litteral du nombre avec symbole '-')
2 - on allour i + 1 pour laisser une place au '\0'a
3 - Cas nb == 0 : On retourne la chaine de caractere : str = "0\0";
4 - Cas nb < 0  : On met un '-' au debut de la chaine, et on transforme nbr
	en un naombre positif avec une multiplication negatif * negatif
5 - Ici, notre nombre est forcement superieur a 0, donc on peut cook :
	str[i] sera egal a nbr % 10 c'est a dire le dernier chiffre du nombre
	actuel, et ce, jusqu'a que nbr soit egal a 0.
	Pour ca, a chaque iteration, on divise nbr par 10.
	Et bien sur, on transforme notre int en ascii en faisant + '0' (48).
*/
char	*ft_itoa(int n)
{
	long	nbr;
	int		i;
	char	*str;

	nbr = n;
	i = get_nbr_len(nbr);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
