/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:43:36 by kevisout          #+#    #+#             */
/*   Updated: 2024/07/24 23:51:19 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_putchar_fd ecrit le caractere 'c' dans le file descriptor 'fd'.
Dans la console comme a la piscine, on mettrais fd = 1 par defaut.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
