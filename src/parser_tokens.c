/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:21 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/11 15:52:31 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Get current token without advancing */
char	*peek_token(t_shell *shell)
{
	if (shell->parser.token_index >= shell->parser.token_count)
		return (NULL);
	return (shell->parser.tokens[shell->parser.token_index]);
}

/* Get current token and advance to next token*/
char	*next_token(t_shell *shell)
{
	char	*token;

	token = peek_token(shell);
	if (token)
		shell->parser.token_index++;
	return (token);
}

