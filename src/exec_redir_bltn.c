/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_bltn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:39:31 by kevso             #+#    #+#             */
/*   Updated: 2025/06/08 18:39:46 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Handle the ">" redirection."
Redirects STDOUT to the specified file.
*/
int	handle_redir_out_bltn(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/*
Handle the ">>" redirection.
Redirects STDOUT to the specified file, appending to it.
*/
int	handle_redir_append_bltn(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/*
Handle the "<" redirection.
Redirects STDIN from the specified file.
*/
int	handle_redir_in_bltn(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/*
Handle the "<<" redirection.
Redirects STDIN from a heredoc file.
The heredoc is handled separately before this function is called,
this one justs opens the file and redirects STDIN to it.
*/
int	handle_redir_heredoc_bltn(t_redir *redir)
{
	int	fd;

	fd = open(redir->heredoc_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections_bltn(t_simple_cmds *cmd)
{
	t_redir	*redir;
	int		ret;

	redir = cmd->redirects;
	while (redir)
	{
		ret = 0;
		if (redir->type == REDIR_OUT)
			ret = handle_redir_out_bltn(redir);
		else if (redir->type == REDIR_APPEND)
			ret = handle_redir_append_bltn(redir);
		else if (redir->type == REDIR_IN)
			ret = handle_redir_in_bltn(redir);
		else if (redir->type == REDIR_HEREDOC)
			ret = handle_redir_heredoc_bltn(redir);
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
