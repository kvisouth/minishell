/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:45:58 by kevisout          #+#    #+#             */
/*   Updated: 2024/07/24 23:54:16 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putendl_fd c'est litteralement ft_putstr_fd qui met un \n a la fin.
On peut se permettre le luxe de verifier si s est NULL ou non.

On pourrait mettre ft_putstr_fd et ft_putchar_fd, mais je prefere ne pas aller
chercher d'autres fichier pour optimiser le truc
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
			i++;
		write(fd, s, i);
		write(fd, "\n", 1);
	}
}
