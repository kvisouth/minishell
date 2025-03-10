/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:45:21 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/10 20:35:28 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Get current token without advancing */
char	*peek_token(t_shell *shell)
{
	if (shell->parser.token_index >= shell->parser.token_count)
		return (NULL);
	return (shell->parser.tokens[shell->parser.token_index]);
}

/* Get current token and advance to next token*/
char	*next_token(t_shell *shell)
{
	char	*token;

	token = peek_token(shell);
	if (token)
		shell->parser.token_index++;
	return (token);
}

/* Parse a redirection token and create a redirection structure */
t_redir	*parse_redirection(char *token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	
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
	
	return (redir);
}

t_cmd *handle_redirection(t_cmd *cmd, t_shell *shell)
{
	char    *redir_token;
	char    *file_token;
	t_redir *redir;

	redir_token = next_token(shell);
	file_token = next_token(shell);
	if (!file_token)
	{
		free_cmd(cmd);
		return (NULL);
	}
	redir = parse_redirection(redir_token);
	if (!redir)
	{
		free_cmd(cmd);
		return (NULL);
	}
	redir->file = ft_strdup(file_token);
	if (!redir->file)
	{
		free(redir);
		free_cmd(cmd);
		return (NULL);
	}
	redir->next = cmd->redirects;
	cmd->redirects = redir;
	
	return (cmd);
}

/* Free a command structure recursively */
void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*next;
	int		i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	redir = cmd->redirects;
	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
	if (cmd->left)
		free_cmd(cmd->left);
	if (cmd->right)
		free_cmd(cmd->right);
	free(cmd);
}


void fill_arguments(t_cmd *cmd, t_shell *shell)
{
	int     i;
	char    *token;

	i = 0;
	while ((token = peek_token(shell)) && !is_pipe(token))
	{
		if (is_redirection(token))
		{
			if (!handle_redirection(cmd, shell))
				return ;
		}
		else
		{
			cmd->args[i++] = ft_strdup(next_token(shell));
			if (!cmd->args[i])
			{
				cmd->args[i] = NULL;
				return ;
			}
		}
	}
	cmd->args[i] = NULL;
}
