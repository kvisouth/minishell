/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:27 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/11 18:59:38 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
ft_striteri applique la fonction 'f' a tout les caracteres de son char* et lui
donne son index en 1er argument.
On passe a (*f) s + i pour passer un pointeur vers le debut de 's' (sachant que
on veut que ce soit la meme lettre que s[i] qui, lui, incremente..)
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, s + i);
		i++;
	}
}
