/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:17:07 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/10 17:48:03 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strnstr cherche little dans big. Si il trouve little dans big, il retourne
un pointeur vers la premiere occurence de big ou little a ete trouvee et ce 
jusqu'a len.
On cast les valeurs de retours car ft_strnstr retourne un *char et on manipule
des const char*
Renvoie NULL si il ne trouve rien.
Renvoie big si little est vide.	(On differencie chaine vide et chaine NULL !)
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little || !little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && little[j]
			&& i + j < len)
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
