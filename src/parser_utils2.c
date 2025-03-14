/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:18:59 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/13 01:12:39 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_redirection(t_simple_cmds *cmd, t_redir *redir)
{
	t_redir *last;

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

int add_argument(t_simple_cmds *cmd, char *word, int i)
{
	cmd->str[i] = ft_strdup(word);
	if (!cmd->str[i])
		return (0);
	return (1);
}

int	process_token(t_shell *shell, t_simple_cmds *cmd, int *i)
{
	char	*token;
	t_redir	*redir;

	token = peek_token(shell);
	if (!token)
		return (0);
	if (is_pipe(token))
		return (0);
	if (is_redirection(token))
	{
		redir = parse_redirection(shell);
		if (!redir)
			return (0);
		if (!add_redirection(cmd, redir))
			return (0);
	}
	else
	{
		if (!add_argument(cmd, token, *i))
			return (0);
		(*i)++;
		next_token(shell);
	}
	return (1);
}

/* Free a simple command structure and all its resources */
void	free_simple_cmd(t_simple_cmds *cmd)
{
    t_simple_cmds	*next_cmd;
    t_redir			*redir;
    t_redir			*next_redir;
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
        redir = cmd->redirects;
        while (redir)
        {
            next_redir = redir->next;
            if (redir->file)
                free(redir->file);
            free(redir);
            redir = next_redir;
        }
        free(cmd);
        cmd = next_cmd;
    }
}
