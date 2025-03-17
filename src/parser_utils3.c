/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:42:41 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/14 20:20:11 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Get and validate redirection tokens */
int	get_redirection_tokens(t_shell *shell, char **token, char **target)
{
	*token = next_token(shell);
	if (!*token || !is_redirection(*token))
		return (0);
	*target = next_token(shell);
	if (!*target)
		return (0);
	return (1);
}

/* Create redirection structure from tokens */
t_redir	*create_redirection(char *token, char *target)
{
	t_redir_type	type;

	if (ft_strcmp(token, "<") == 0)
		type = REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		type = REDIR_OUT;
	else if (ft_strcmp(token, ">>") == 0)
		type = REDIR_APPEND;
	else if (ft_strcmp(token, "<<") == 0)
		type = REDIR_HEREDOC;
	else
		type = REDIR_NONE;
	if (type == REDIR_NONE)
		return (NULL);
	return (init_redirection(type, target));
}

t_redir	*init_redirection(t_redir_type type, char *target)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(target);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

t_simple_cmds	*prepare_simple_cmd(t_shell *shell, int *word_count)
{
	t_simple_cmds	*cmd;

	*word_count = count_words(shell);
	cmd = create_simple_cmd();
	cmd = alloc_cmd_args(cmd, *word_count);
	if (!cmd)
		return (NULL);
	return (cmd);
}

/* Process tokens for a simple command */
t_simple_cmds	*process_simple_cmd(t_shell *shell,
		t_simple_cmds *cmd, int word_count)
{
	int		i;
	char	*token;

	i = 0;
	token = peek_token(shell);
	while ((token) && !is_pipe(token))
	{
		if (i >= word_count && !is_redirection(token))
			break ;
		if (!process_token(shell, cmd, &i))
		{
			free_simple_cmd(cmd);
			return (NULL);
		}
		token = peek_token(shell);
	}
	cmd->str[i] = NULL;
	check_if_builtin(cmd);
	return (cmd);
}
