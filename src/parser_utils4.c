/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:26:15 by abreuil           #+#    #+#             */
/*   Updated: 2025/06/08 13:33:23 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	process_redirection_token(t_shell *shell, t_simple_cmds *cmd)
{
	t_redir	*redir;

	redir = parse_redirection(shell);
	if (!redir)
		return (0);
	if (!add_redirection(cmd, redir))
		return (0);
	return (1);
}

int	process_argument_token(t_shell *shell, t_simple_cmds *cmd, int *i)
{
	char	*token;
	char	*unquoted;

	token = peek_token(shell);
	unquoted = remove_quotes(token);
	if (!unquoted)
		return (0);
	if (!add_argument(cmd, unquoted, *i))
	{
		free(unquoted);
		return (0);
	}
	free(unquoted);
	(*i)++;
	next_token(shell);
	return (1);
}
