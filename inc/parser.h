/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:19:02 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/09 16:26:30 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <string.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <stdbool.h>
# include "../inc/minishell.h"
# include "../inc/lexer.h"
# include "../libft/libft.h"

/* Command types */
typedef enum e_cmd_type
{
    CMD_SIMPLE,     // Simple command (e.g., ls -la)
    CMD_PIPE,       // Pipeline (e.g., ls | grep a)
    CMD_REDIR       // Redirection (e.g., ls > file)
} t_cmd_type;

/* Redirection types */
typedef enum e_redir_type
{
    REDIR_IN,       // Input redirection (<)
    REDIR_OUT,      // Output redirection (>)
    REDIR_APPEND,   // Append output redirection (>>)
    REDIR_HEREDOC   // Here document (<<)
} t_redir_type;

/* Redirection structure */
typedef struct s_redir
{
    t_redir_type    type;
    char            *file;
    struct s_redir  *next;
} t_redir;

/* Command structure */
typedef struct s_cmd
{
    t_cmd_type      type;
    char            **args;         // Command arguments (args[0] is the command)
    t_redir         *redirects;     // Linked list of redirections
    struct s_cmd    *left;          // Left command in a pipeline
    struct s_cmd    *right;         // Right command in a pipeline
} t_cmd;

/* Parser structure */
typedef struct s_parser
{
    char            **tokens;       // Tokens from lexer
    int             token_index;    // Current token index
    int             token_count;    // Total number of tokens
} t_parser;

/* Function prototypes for parser */
int     parser(t_shell *shell);
t_cmd   *parse_command(t_shell *shell);
t_cmd   *parse_pipeline(t_shell *shell);
t_cmd   *parse_simple_command(t_shell *shell);
t_redir *parse_redirection(t_shell *shell, char *token);
void    free_cmd(t_cmd *cmd);

#endif