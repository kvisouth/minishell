/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 16:30:28 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unlink_heredoc(void)
{
	if (access(".heredoc", F_OK) == -1)
		return ;
	if (unlink(".heredoc") == 1)
	{
		perror("Error unlinking .heredoc");
		exit(1);
	}
}

int	exec(t_shell *shell)
{
	count_cmds(shell);
	format_cmds(shell);
	if (!process_all_heredocs(shell))
	{
		unlink_heredoc();
		free_minishell(shell);
		return (0);
	}
	if (shell->nb_cmds > 1)
		execute_pipeline(shell);
	else
	{
		if (shell->simple_cmds->builtin)
			execute_builtin(shell, shell->simple_cmds);
		else
			execute_command(shell, shell->simple_cmds);
	}
	unlink_heredoc();
	return (0);
}
