/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:07:22 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/11 15:37:34 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  Check if the first token is a pipe */
int	handle_pipe(t_shell *shell, int token_count)
{
	if (is_pipe(shell->lexer.tokens[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	if (is_pipe(shell->lexer.tokens[token_count - 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}

// Check if there are two consecutive operators
int handle_operator(t_shell *shell, int token_count, int i)
{
	char *curr_token;
	char *next_token;
	
	curr_token = shell->lexer.tokens[i];
	if (i < token_count - 1)
		next_token = shell->lexer.tokens[i + 1];
	else
		next_token = NULL;
	if (ft_strlen(curr_token) > 2 &&
		(curr_token[0] == '>' || curr_token[0] == '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(curr_token, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	check_consecutive_ops(curr_token, next_token);
	return (1);
}

// Check if there is a redirection without a target
int handle_no_redirect(t_shell *shell, int token_count, int i, int *skip)
{
	*skip = 0;
	if (is_redirection(shell->lexer.tokens[i]))
	{
		if (i == token_count - 1 || is_operator(shell->lexer.tokens[i + 1]))
		{
			ft_putstr_fd("minishell: syntax error: missing redirect target\n", 2);
			return (0);
		}
		*skip = 1;
	}
	return (1);
}
// Check if there is an empty command between two pipes
int	handle_empty_command_between_pipe(t_shell *shell, int token_count, int i)
{
	if (i > 0 && i < token_count - 1 && 
		is_pipe(shell->lexer.tokens[i - 1]) && is_pipe(shell->lexer.tokens[i + 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}
// main function to validate tokens
int	validate_tokens(t_shell *shell)
{
	int	i;
	int	token_count;
	int	skip;

	if (!shell->lexer.tokens || !shell->lexer.tokens[0])
		return (1);
	token_count = shell->lexer.token_count;
	if (!handle_pipe(shell, token_count))
		return (0);
	i = 0;
	while (i < token_count)
	{
		skip = 0;
		if (!handle_operator(shell, token_count, i))
			return (0);
		if (!handle_no_redirect(shell, token_count, i, &skip))
			return (0);
		if (!handle_empty_command_between_pipe(shell, token_count, i))
			return (0);
		i += (skip + 1);
	}
	return (1);
}
