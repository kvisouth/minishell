/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:21 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/12 02:37:35 by abreuil          ###   ########.fr       */
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
	redir->file = ft_strdup(target);
	redir->next = NULL;
	return (redir);
}

t_simple_cmds	*parse_pipeline(t_shell *shell)
{
	t_simple_cmds *current_cmd;
	t_simple_cmds *next_cmd;
	t_simple_cmds *first_cmd;
	char *token;

	first_cmd = parse_simple_cmd(shell);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	
	
}

