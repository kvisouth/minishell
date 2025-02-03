/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:20:59 by kevisout          #+#    #+#             */
/*   Updated: 2024/07/25 00:27:00 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putstr_fd ecris la chaine de caractere 's' sur la sortie 'fd'.
On evite de faire un boucle qui fait write() car write est un syscall.
Et spammer un syscall c'est pas optimisee, donc on calcule la longueur de s
pour ecrire s avec 1 seul write().
*/
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}
