/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:13:57 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 14:14:18 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		end(1, TRUE, NULL);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redir_heredoc(t_redir *redir)
{
	int	fd;

	fd = open(redir->heredoc_file, O_RDONLY);
	if (fd == -1)
		end(1, TRUE, "open failed");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redirections(t_simple_cmds *cmd)
{
	t_redir	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			handle_redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			handle_redir_append(redir);
		else if (redir->type == REDIR_IN)
			handle_redir_in(redir);
		else if (redir->type == REDIR_HEREDOC)
			handle_redir_heredoc(redir);
		redir = redir->next;
	}
}
