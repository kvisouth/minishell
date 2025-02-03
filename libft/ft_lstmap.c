/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:18:00 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/18 17:31:10 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstmap creer une nouvelle liste, cette nouvelle liste est le resultat
de la liste 'lst' apres avoir ete iteree par la fonction 'f'.

Au debut on creer un maillon de liste, qui contient le resultat de iter (f).
Si un malloc echoue, on efface cette liste avec ft_lstclear et (del).
Ensuite, on ajoute ce maillon a la nouvelle liste 'new' avec ft_lstadd_back.
Puis on fonce sur le prochain maillon.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*node;

	if (!lst)
		return (NULL);
	tmp = lst;
	new = NULL;
	while (tmp)
	{
		node = ft_lstnew((*f)(tmp->content));
		if (!node)
			return (ft_lstclear(&new, del), NULL);
		ft_lstadd_back(&new, node);
		tmp = tmp->next;
	}
	return (new);
}
