/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:09:49 by abreuil           #+#    #+#             */
/*   Updated: 2025/06/08 13:24:58 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_shell_struct(t_shell *shell)
{
	shell->env = NULL;
	shell->cmdline = NULL;
	shell->path = NULL;
	shell->simple_cmds = NULL;
	shell->nb_cmds = 0;
	shell->end = false;
	shell->pipefd[0] = -1;
	shell->pipefd[1] = -1;
	shell->lexer.tokens = NULL;
	shell->lexer.token_count = 0;
	shell->lexer.new_cmdline = NULL;
	shell->lexer.inside_quotes = false;
	shell->lexer.quote_char = '\0';
	shell->parser.tokens = NULL;
	shell->parser.token_count = 0;
	shell->parser.token_index = 0;
	shell->heredoc_flag = 0;
	shell->lexer.new_cmdline = NULL;
	shell->lexer.tokens = NULL;
	shell->lexer.token_count = 0;
	shell->lexer.inside_quotes = false;
	shell->lexer.quote_char = '\0';
}
