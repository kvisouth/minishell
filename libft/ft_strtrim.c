/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:57:27 by kevisout          #+#    #+#             */
/*   Updated: 2024/11/13 18:58:24 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
is_trim retourne 1 si la lettre en parametre est une lettre du *set
*/

static int	is_trim(const char letter, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (letter == set[i])
			return (1);
		i++;
	}
	return (0);
}

/*
	Etape 1 : il ignore les caracteres a trimmer a gauche avec i
	Etape 2 : parel a droite avec j, jusqu'a croiser i.
	Ducoup on sait quon malloc i-j + 1 pour le \0
	Etape 3 : On copie la chaine de i a j dans notre nouvelle string.
*/

char	*ft_strtrim(const char *s, const char *set)
{
	char	*str;
	int		size;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = ft_strlen(s) - 1;
	while (is_trim(s[i], set) == 1 && s[i])
		i++;
	while (is_trim(s[j], set) == 1 && j > i)
		j--;
	size = (j - i) + 1;
	str = malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	n = 0;
	while (i <= j)
		str[n++] = s[i++];
	str[n] = '\0';
	return (str);
}

/*
int	main (int ac, char **av)
 {
 	if (ac == 3)
 	{
 	char *s1 = av[1];
 	char *set = av[2];
 	printf("Voici le trimage: %s",ft_strtrim(s1, set));
 	}
 }

 int	main (void)
 {
 	char *s1 = "++yo+mec++";
 	char *set = "+";
 	printf("Voici le trimage: %s",ft_strtrim(s1, set));
 }
*/
