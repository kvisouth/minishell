/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/12 02:27:30 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void init_parser(t_parser *parser, t_lexer *lexer)
{
    parser->tokens = lexer->tokens;
    parser->token_count = lexer->token_count;
    parser->token_index = 0;
}

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

