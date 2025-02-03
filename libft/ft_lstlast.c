/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:23:44 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/17 23:38:42 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstlast retourne un pointeur vers le dernier maillon de la liste.
Simplement, tant que lst->next n'est pas NULL, on avance dans la liste

C'est important de verifier si lst est NULL car si on lit dans lst alors
qu'il est nul c'est le SIGSEGV assuree. (Je vais le rajouter aux autres
fonctions lst d'ailleurs)
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
