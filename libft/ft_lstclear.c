/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:57:28 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/17 23:45:07 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstclear supprime et free() tout les maillons de 'lst'

On fait en sorte que notre liste 'tmp' soit egal au prochain maillon. (next)
On supprime 'content' avec (*del)
On free le maillon *lst
Maintenant que tout est supp. et free. on saute sur le prochain maillon
en affectant tmp a lst qu'on avait sauvegardee au debut de la boucle.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
