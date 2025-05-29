/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:42:00 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/29 13:42:24 by abreuil          ###   ########.fr       */
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
	free_tab(shell->lexer.tokens);
	free(shell->lexer.new_cmdline);
	while (shell->simple_cmds)
	{
		tmp = shell->simple_cmds->next;
		free_simple_cmd_exec(shell->simple_cmds);
		shell->simple_cmds = tmp;
	}
}
