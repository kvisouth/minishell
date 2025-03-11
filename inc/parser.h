/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:19:02 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/11 14:57:36 by kevso            ###   ########.fr       */
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
    struct s_cmd    *prev;          // Left command in a pipeline
    struct s_cmd    *next;         // Right command in a pipeline
} t_cmd;

/* Parser structure */
typedef struct s_parser
{
    char            **tokens;       // Tokens from lexer
    int             token_index;    // Current token index
    int             token_count;    // Total number of tokens
} t_parser;

/* Token validation */
int	validate_tokens_for_parser(t_shell *shell);
int	validate_tokens(t_shell *shell);
int	is_redirection(char *token);
int	is_pipe(char *token);
int	is_operator(char *token);
int	ft_strcmp(const char *s1, const char *s2);
char    *peek_token(t_shell *shell);
char    *next_token(t_shell *shell);


/* Function prototypes for parser */
t_redir	*parse_redirection(char *token);
t_cmd	*handle_redirection(t_cmd *cmd, t_shell *shell);
void	fill_arguments(t_cmd *cmd, t_shell *shell);
t_cmd	*parse_simple_command(t_shell *shell);
t_cmd	*parse_pipeline(t_shell *shell);
int		parser(t_shell *shell);
void	free_cmd(t_cmd *cmd);



#endif