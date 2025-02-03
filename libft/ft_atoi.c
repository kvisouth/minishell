/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:44:52 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/12 21:28:02 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_atoi prend en parametre une chaine de caracteres, et la convertit en int.
La string doit etre sous cette forme :
- Commence par des whitespaces
- Suivi d'un seul symbole + ou - (ou aucun)
- Suivi de chiffres.
Le parsing s'arrete d'est qu'une de ses regles n'est pas respectee.
*/

int	ft_atoi(const char *str)
{
	int	pos;
	int	nbr;
	int	i;

	pos = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pos = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * pos);
}

/*
int	main(int ac, char **av)
{
	if (ac != 2)
	  return (0);
	printf("atoi    = '%d'\n", atoi(av[1]));
	printf("ft_atoi = '%d'\n", ft_atoi(av[1]));
	return (1);
}
*/
