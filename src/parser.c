/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/05/29 13:41:30 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_parser(t_parser *parser, t_lexer *lexer)
{
	parser->tokens = lexer->tokens;
	parser->token_count = lexer->token_count;
	parser->token_index = 0;
}

/*this function will count the number of words in the command line */
int	count_words(t_shell *shell)
{
	int	i;
	int	count;

	i = shell->parser.token_index;
	count = 0;
	while (i < shell->parser.token_count)
	{
		if (is_pipe(shell->parser.tokens[i]))
			break ;
		if (is_redirection(shell->parser.tokens[i]))
		{
			i++;
			if (i < shell->parser.token_count)
				i++;
			continue ;
		}
		if (!is_operator(shell->parser.tokens[i]))
			count++;
		i++;
	}
	return (count);
}

/*this function will allocate memory for the command and its arguments */
t_simple_cmds	*create_simple_cmd(void)
{
	t_simple_cmds	*cmd;

	cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->builtin = false;
	cmd->pid = 1;
	return (cmd);
}

void	print_commands(t_simple_cmds *cmds)
{
	t_simple_cmds	*current;
	int				i;

	current = cmds;
	while (current)
	{
		i = 0;
		while (current->str && current->str[i])
		{
			i++;
		}
		current = current->next;
	}
}

int	parser(t_shell *shell)
{
	init_parser(&shell->parser, &shell->lexer);
	shell->simple_cmds = parse_pipeline(shell);
	return (shell->simple_cmds != NULL);
}
