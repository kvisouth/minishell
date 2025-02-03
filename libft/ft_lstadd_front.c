/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:39:28 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/17 18:56:58 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstadd_front ajoute l'element 'new' au debut de la liste 'lst'

On fait en sorte que le l'element 'next' du maillon 'new' pointe sur le premier
madaillon de 'lst'. Ensuite on fait en sorte que le pointeur vers le debut
la liste 'lst' soit egal a 'new' pour que le debut de la liste 'lst' soit le
nouveau maillon. (On actualise en gros.)
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
