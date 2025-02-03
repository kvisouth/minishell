/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:54:38 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/17 23:22:23 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_lstnew cree une nouvelle liste.
Cette nouvelle liste ne contient qu'un maillon avec les elements
content et next.
content sera egal au parametre, et next sera egal a NULL.

Pour ajouter des elements a la liste, il faut utiliser
ft_lstadd_back ou ft_lstadd_front.
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
