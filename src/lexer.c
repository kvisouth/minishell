/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/11 13:05:37 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	lexer(t_shell *shell)
{
	if (shell->cmdline[0] == '\0' || shell->cmdline[0] == '\n')
		return (0);
	shell->new_cmdline = add_spaces_to_cmdline(shell->cmdline, &shell->lexer);
	if (!shell->new_cmdline)
		return (0);
	shell->lexer.token_count = count_tokens(shell->new_cmdline, &shell->lexer);
	shell->lexer.tokens = split_tokens(shell->new_cmdline, &shell->lexer);
	if (!shell->lexer.tokens)
		return (0);
	if (!validate_tokens_for_parser(shell))
	{
		free_tab(shell->lexer.tokens);
		shell->lexer.tokens = NULL;
		return (0);
	}
	return (1);
}

//TODO LIST :
// - retirer les quotes des tokens : ls"caca" --> lscaca
//    (ce qui est COLLER aux exterieurs des quotes)