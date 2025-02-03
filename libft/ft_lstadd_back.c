/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:21:28 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/17 18:41:47 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst : L'adresse du pointeur vers le premier element de la liste
(Pointeur sur notre liste)
new : L'adresse du pointeur vers l'element a ajouter dans la liste
(Pointeur sur un maillon pas encore dans la liste)

ft_lstadd_back ajoute un maillon a la fin de la liste.

Encore une fois, on avance dans la liste avec une variable tmp pour ne pas
perdre notre pointeur.
On verifie premierement si lst est NULL, si oui alors il n'y a pas de maillon
dans notre liste ou on est deja sur le dernier, donc on met le maillong new ici

Sinon, on se place sur le dernier maillon de la liste avec ft_lstlast, puis
on fait en sorte que next (qui est egal a NULL avec lstlast car dernier
element de la liste) est maintenant egal a new. (Le nouveau maillon)

*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
