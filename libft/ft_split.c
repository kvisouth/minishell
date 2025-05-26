/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:57:05 by kevisout          #+#    #+#             */
/*   Updated: 2025/05/26 12:52:57 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* En cas d'echec de la part de malloc, cette fonction sera appelee */
static void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

/* Retourne le nombre de mots dont split a besoin pour malloc */
static int	count_words(char const *s, char sep)
{
	int	cpt;
	int	i;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		if (s[i] != sep && s[i])
			cpt++;
		while (s[i] != sep && s[i])
			i++;
	}
	return (cpt);
}

/* Retourne le mot que split doit ranger dans son tableau */
static char	*dup_str(char const *s, char sep)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s[i] != sep && s[i])
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

/*
ft_split decoupe une string pour ranger chaque "mot" dans un tableau
(char *). Chaque mot est separee par le separateur 'c'.
*/
char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			tab[i] = dup_str(s, c);
			if (!tab[i])
				return (free_all(tab), NULL);
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
