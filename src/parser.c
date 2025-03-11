/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/11 16:53:40 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int validate_tokens_for_parser(t_shell *shell)
{
    if (!validate_tokens(shell))
        return (0);
    return (1);
}

t_simple_cmds *create_simple_cmd(void)
{
    t_simple_cmds *cmd;

    cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
    if (!cmd)
        return (NULL);
    cmd->str = NULL;
    cmd->builtin = NULL;
    cmd->num_redirections = 0;
    cmd->hd_file_name = NULL;
    cmd->redirections = NULL;
    cmd->next = NULL;
    cmd->prev = NULL;
    return (cmd);
}

int count_args_till_pipe(t_shell *shell, int start_idx)
{
    int i;
    int count;

    i = start_idx;
    count = 0;
    while (i < shell->lexer.token_count && !is_pipe(shell->lexer.tokens[i]))
    {
        if (is_redirection(shell->lexer.tokens[i]))
            i += 2; // Skip the redirection and its target
        else
        {
            count++;
            i++;
        }
    }
    return (count);
}

int parser(t_shell *shell)
{
    int i;
    int j;
    int arg_count;
    t_simple_cmds *current;
    t_simple_cmds *prev;

    if (!validate_tokens_for_parser(shell))
        return (0);
    i = 0;
    prev = NULL;
    shell->simple_cmds = NULL;
    while (i < shell->lexer.token_count)
    {
        // Create a new command node
        current = create_simple_cmd();
        if (!current)
            return (0);
        if (prev)
        {
            prev->next = current;
            current->prev = prev;
        }
        else
            shell->simple_cmds = current;
        arg_count = count_args_till_pipe(shell, i);
        current->str = (char **)malloc(sizeof(char *) * (arg_count + 1));
        if (!current->str)
            return (0);
        j = 0;
        while (j < arg_count && i < shell->lexer.token_count)
        {
            if (is_redirection(shell->lexer.tokens[i]))
            {
                i += 2;
                continue;
            }
            else if (is_pipe(shell->lexer.tokens[i]))
                break;
                
            current->str[j] = ft_strdup(shell->lexer.tokens[i]);
            j++;
            i++;
        }
        current->str[j] = NULL;
        if (i < shell->lexer.token_count && is_pipe(shell->lexer.tokens[i]))
            i++;
            
        prev = current;
    }
    return (1);
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

