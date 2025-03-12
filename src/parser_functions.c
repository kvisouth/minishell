/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:21 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/12 17:12:04 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Parse a redirection token (< , >  , << , >>) */
t_redir		*parse_redirection(t_shell *shell)
{
	t_redir *redir;
	char *token;
	char *target;

	token = next_token(shell);
	if (!token || !is_redirection(token))
		return (NULL);
	target = next_token(shell);
	if (!target)
		return (NULL);
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (ft_strcmp(token, "<") == 0)
		redir->type = REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		redir->type = REDIR_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		redir->type = REDIR_APPEND;
	else if (ft_strcmp(token, "<<") == 0)
		redir->type = REDIR_HEREDOC;
	else
	{
		free(redir);
		return (NULL);
	}
	redir->file = ft_strdup(target);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}
t_simple_cmds	*alloc_cmd_args(t_simple_cmds *cmd, int word_count)
{
	if (!cmd)
		return (NULL);
	if (word_count == 0)
	{
		cmd->str = malloc(sizeof(char *));
		if (!cmd->str)
		{
			free(cmd);
			return (NULL);
		}
		cmd->str[0] = NULL;
	}
	else
	{
		cmd->str = malloc(sizeof(char *) * word_count + 1);
		if (!cmd->str)
		{
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}
t_simple_cmds    *parse_simple_cmd(t_shell *shell)
{
    t_simple_cmds	*cmd;
	int				word_count;
	int				i;
	char			*token;

	word_count = count_words(shell);
	cmd = create_simple_cmd();
	cmd = alloc_cmd_args(cmd, word_count);
	if (!cmd)
		return (NULL);
	i = 0;
	while((token = peek_token(shell)) && !is_pipe(token))
	{
		if (!process_token(shell, cmd, &i))
		{
			free_simple_cmd(cmd);
			return (NULL);
		}
	}
	if (word_count == 0)
		cmd->str[i] = NULL;
	check_if_builtin(cmd);
	return (cmd);
}


t_simple_cmds	*parse_pipeline(t_shell *shell)
{
	t_simple_cmds	*current_cmd;
	t_simple_cmds	*next_cmd;
	t_simple_cmds 	*first_cmd;
	char			*token;

	first_cmd = parse_simple_cmd(shell);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	while((token = peek_token(shell)) && is_pipe(token))
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
