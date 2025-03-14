/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:21 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/14 18:01:45 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Parse a redirection token (< , >  , << , >>) */
t_redir	*parse_redirection(t_shell *shell)
{
	char	*token;
	char	*target;

	if (!get_redirection_tokens(shell, &token, &target))
		return (NULL);
	return (create_redirection(token, target));
}

t_simple_cmds	*alloc_cmd_args(t_simple_cmds *cmd, int word_count)
{
	if (!cmd)
		return (NULL);
	if (word_count == 0)
	{
		cmd->str = malloc(sizeof(char *) * 1);
		if (!cmd->str)
		{
			free(cmd);
			return (NULL);
		}
		cmd->str[0] = NULL;
	}
	else
	{
		cmd->str = malloc(sizeof(char *) * (word_count + 1));
		if (!cmd->str)
		{
			free(cmd);
			return (NULL);
		}
		cmd->str[word_count] = NULL;
	}
	return (cmd);
}

t_simple_cmds	*parse_simple_cmd(t_shell *shell)
{
	t_simple_cmds		*cmd;
	int					word_count;

	cmd = prepare_simple_cmd(shell, &word_count);
	if (!cmd)
		return (NULL);
	return (process_simple_cmd(shell, cmd, word_count));
}

t_simple_cmds	*parse_pipeline(t_shell *shell)
{
	t_simple_cmds	*current_cmd;
	t_simple_cmds	*next_cmd;
	t_simple_cmds	*first_cmd;
	char			*token;

	first_cmd = parse_simple_cmd(shell);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	token = peek_token(shell);
	while ((peek_token(shell)) && is_pipe(token))
	{
		next_token(shell);
		next_cmd = parse_simple_cmd(shell);
		if (!next_cmd)
		{
			free_simple_cmd(first_cmd);
			return (NULL);
		}
		current_cmd->next = next_cmd;
		next_cmd->prev = current_cmd;
		current_cmd = next_cmd;
	}
	return (first_cmd);
}
