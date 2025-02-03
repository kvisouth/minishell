/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:57:17 by kevisout          #+#    #+#             */
/*   Updated: 2024/07/25 00:21:17 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putnbr_fd ecris l'entier n sur la sortie fd.
La recursivite ca prend + de RAM que de l'iteratif, et vu que je veux une
libft performante, putnbr sera ici iteratif. (Coucou Seb)

- On prend un buffer de 11 car 11 est la longueur maximale d'un entier :
Le principe ici sera de remplir notre buffer a l'envers en incrementant i
Puis d'ecrire notre buffer en decrementant i.

Donc quand on a : n = -25
Notre buffer ressemblera a : 52-
Puis on va ecire le '-' puis le '2' puis le '5' et on aura bien : -25
sur notre fd.
*/
void	ft_putnbr_fd(int n, int fd)
{
	char	buff[11];
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	if (n < 0)
	{
		neg = 1;
		if (n == -2147483648)
			return ((void)write(fd, "-2147483648", 11));
		n *= -1;
	}
	while (n > 0)
	{
		buff[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		buff[i++] = '-';
	while (i--)
		ft_putchar_fd(buff[i], fd);
}
