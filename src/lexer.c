/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/05 01:06:49 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// adds a spaces before and after operators if they are not already there
// operators are : |, ;, <, >, &
char	*add_spaces_to_cmdline(char *cmdline)
{
	char	*new_cmdline;
	int		i;

	new_cmdline = ft_calloc(ft_strlen(cmdline) * 2 + 1, sizeof(char));
	if (!new_cmdline)
		return (NULL);
	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '|' || cmdline[i] == ';' || cmdline[i] == '<' || cmdline[i] == '>' || cmdline[i] == '&')
		{
			if (i > 0 && cmdline[i - 1] != ' ')
				ft_strlcat(new_cmdline, " ", ft_strlen(new_cmdline) + 2);
			ft_strlcat(new_cmdline, &cmdline[i], ft_strlen(new_cmdline) + 2);
			if (cmdline[i + 1] && cmdline[i + 1] != ' ')
				ft_strlcat(new_cmdline, " ", ft_strlen(new_cmdline) + 2);
		}
		else
			ft_strlcat(new_cmdline, &cmdline[i], ft_strlen(new_cmdline) + 2);
		i++;
	}
	return (new_cmdline);
}

int	lexer(t_lexer *lex, char *cmdline)
{
	char	*new_cmdline;

	new_cmdline = add_spaces_to_cmdline(cmdline);
	if (!new_cmdline)
		return (0);
	printf("new_cmdline: %s\n", new_cmdline);
	return (1);
	(void)lex;
	(void)cmdline;
}