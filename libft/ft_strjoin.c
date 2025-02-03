/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:40:28 by kevisout          #+#    #+#             */
/*   Updated: 2024/08/05 10:40:58 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strjoin concatene s1 et s2 dans une nouvelle chaine de caractere
(qu' il faut malloc ducoup)
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	ret = malloc ((i + j + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i])
		ret[k++] = s1[i++];
	j = 0;
	while (s2[j])
		ret[k++] = s2[j++];
	ret[k] = '\0';
	return (ret);
}
