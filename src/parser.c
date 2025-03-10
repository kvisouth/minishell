/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/10 20:51:13 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* count arguments excluding redirections */
static int	count_arguments(t_shell *shell)
{
	int		tmp_index;
	char	*token;
	int		arg_count;
	
	tmp_index = shell->parser.token_index;
	arg_count = 0;
	while((token = peek_token(shell)) && !is_pipe(token))
	{
		if (is_redirection(token))
		{
			next_token(shell);
			next_token(shell);
		}
		else
		{
			arg_count++;
			next_token(shell);
		}
	}
	shell->parser.token_index = tmp_index;
	return (arg_count);
}

/* Parse a simple command (command with arguments) */
t_cmd	*parse_simple_command(t_shell *shell)
{
	t_cmd	*cmd;
	int		arg_count;

	arg_count = count_arguments(shell);
	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->type = CMD_SIMPLE;
	cmd->redirects = NULL;
	cmd->left = NULL;
	cmd->right = NULL;
	if (!(cmd->args = malloc(sizeof(char *) * (arg_count + 1))))
	{
		free(cmd);
		return (NULL);
	}
	fill_arguments(cmd, shell);
	return (cmd);
}
/* Parse a pipeline (cmd1 | cmd2 | ... | cmdN) */
t_cmd	*parse_pipeline(t_shell *shell)
{
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*pipe_cmd;
	char	*token;
	
	left = parse_simple_command(shell);
	if (!left)
		return (NULL);
	token = peek_token(shell);
	if (!token || !is_pipe(token))
		return (left);
	next_token(shell);
	right = parse_pipeline(shell);
	if (!right)
	{
		free_cmd(left);
		return (NULL);
	}
	pipe_cmd = malloc(sizeof(t_cmd));
	if (!pipe_cmd)
	{
		free_cmd(left);
		free_cmd(right);
		return (NULL);
	}
	pipe_cmd->type = CMD_PIPE;
	pipe_cmd->args = NULL;
	pipe_cmd->redirects = NULL;
	pipe_cmd->left = left;
	pipe_cmd->right = right;
	return (pipe_cmd);
}

/* main parsing function */
int	parser(t_shell *shell)
{
	shell->parser.tokens = shell->lexer.tokens;
	shell->parser.token_index = 0;
	shell->parser.token_count = shell->lexer.token_count;
	shell->cmd = parse_pipeline(shell);
	return (shell->cmd != NULL);
}
