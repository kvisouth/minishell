/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/13 00:57:21 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_parser(t_parser *parser, t_lexer *lexer)
{
	parser->tokens = lexer->tokens;
	parser->token_count = lexer->token_count;
	parser->token_index = 0;
}
/*this function will count the number of words in the command line */
int count_words(t_shell *shell)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < shell->lexer.token_count)
	{
		if (!is_operator(shell->lexer.tokens[i]))
			count++;
		i++;
	}
	return (count);
}

/*this function will allocate memory for the command and its arguments */
t_simple_cmds *create_simple_cmd(void)
{
	t_simple_cmds *cmd;

	cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->builtin = false;
	return (cmd);
}

void print_commands(t_simple_cmds *cmds)
{
	t_simple_cmds *current;
	int i;
	
	current = cmds;
	while (current)
	{
		printf("Command: ");
		i = 0;
		while (current->str && current->str[i])
		{
			printf("[%s] ", current->str[i]);
			i++;
		}
		printf("\n");
		current = current->next;
	}
}

int parser(t_shell *shell)
{
	init_parser(&shell->parser, &shell->lexer);
	shell->simple_cmds = parse_pipeline(shell);
	return (shell->simple_cmds != NULL);
}