/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:42:00 by abreuil           #+#    #+#             */
/*   Updated: 2025/06/06 12:53:15 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		if (redir->heredoc_file)
			free(redir->heredoc_file);
		free(redir);
		redir = tmp;
	}
}

void	free_simple_cmd_exec(t_simple_cmds *cmd)
{
	if (!cmd)
		return ;
	if (cmd->str)
		free_tab(cmd->str);
	if (cmd->redirects)
		free_redir(cmd->redirects);
	free(cmd);
}

void	free_minishell(t_shell *shell)
{
	t_simple_cmds	*tmp;

	free(shell->cmdline);
	shell->cmdline = NULL;
	free_tab(shell->lexer.tokens);
	shell->lexer.tokens = NULL;
	free(shell->lexer.new_cmdline);
	shell->lexer.new_cmdline = NULL;
	while (shell->simple_cmds)
	{
		tmp = shell->simple_cmds->next;
		free_simple_cmd_exec(shell->simple_cmds);
		shell->simple_cmds = tmp;
	}
}

void	free_expander(t_shell *shell)
{
	if (shell->lexer.new_cmdline)
		free(shell->lexer.new_cmdline);
	if (shell->cmdline)
		free(shell->cmdline);
	if (shell->lexer.tokens)
		free_tab(shell->lexer.tokens);
	shell->lexer.tokens = NULL;
	shell->cmdline = NULL;
	shell->lexer.new_cmdline = NULL;
}
