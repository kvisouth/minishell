/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:18:59 by abreuil           #+#    #+#             */
/*   Updated: 2025/06/08 13:34:35 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_redirection(t_simple_cmds *cmd, t_redir *redir)
{
	t_redir	*last;

	if (!redir)
		return (0);
	if (!cmd->redirects)
		cmd->redirects = redir;
	else
	{
		last = cmd->redirects;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (1);
}

int	add_argument(t_simple_cmds *cmd, char *word, int i)
{
	cmd->str[i] = ft_strdup(word);
	if (!cmd->str[i])
		return (0);
	return (1);
}

int	process_token(t_shell *shell, t_simple_cmds *cmd, int *i)
{
	char	*token;

	token = peek_token(shell);
	if (!token)
		return (0);
	if (is_pipe(token))
		return (0);
	if (is_redirection(token))
		return (process_redirection_token(shell, cmd));
	else
		return (process_argument_token(shell, cmd, i));
}

void	free_redirections(t_redir *redir)
{
	t_redir	*next_redir;

	while (redir)
	{
		next_redir = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = next_redir;
	}
}

/* Free a simple command structure and all its resources */
void	free_simple_cmd(t_simple_cmds *cmd)
{
	t_simple_cmds	*next_cmd;
	int				i;

	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->str)
		{
			i = 0;
			while (cmd->str[i])
			{
				free(cmd->str[i]);
				cmd->str[i] = NULL;
				i++;
			}
			free(cmd->str);
			cmd->str = NULL;
		}
		free_redirections(cmd->redirects);
		cmd->redirects = NULL;
		free(cmd);
		cmd = next_cmd;
	}
}
