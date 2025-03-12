/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:19:02 by abreuil           #+#    #+#             */
/*   Updated: 2025/03/12 17:22:13 by abreuil          ###   ########.fr       */
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

// command structure with arguments
typedef struct s_simple_cmds
{
	char                    **str; // command and arguments
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
    t_redir                 *redirects;
    bool                    builtin;
}	t_simple_cmds;

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
int   check_consecutive_ops(char *curr_token, char *next_token);
int  handle_operator(t_shell *shell, int token_count, int i);
int  handle_no_redirect(t_shell *shell, int token_count, int i, int *skip);
int  handle_empty_command_between_pipe(t_shell *shell, int token_count, int i);
int handle_pipe(t_shell *shell, int token_count);



/* Function prototypes for parser */
t_redir	*parse_redirection(t_shell *shell);
t_simple_cmds	*handle_redirection(t_simple_cmds *cmd, t_shell *shell);
void	fill_arguments(t_simple_cmds *cmd, t_shell *shell);
t_simple_cmds	*parse_simple_comd(t_shell *shell);
t_simple_cmds	*parse_pipeline(t_shell *shell);
int		parser(t_shell *shell);
t_simple_cmds    *alloc_cmd_args(t_simple_cmds *cmd, int word_count);
t_simple_cmds	*create_simple_cmd(void);


// test functions
void print_commands(t_simple_cmds *cmds);
void test_parser(void);
void init_shell(t_shell *shell);
void free_shell(t_shell *shell);
int  tokenize(t_shell *shell, char *input);

// parser_utils.c
int	is_redirection(char *token);
int	is_pipe(char *token);
int	is_operator(char *token);
int	ft_strcmp(const char *s1, const char *s2);
void    check_if_builtin(t_simple_cmds *cmd);
int	count_words(t_shell *shell);
int add_argument(t_simple_cmds *cmd, char *word, int i);
int	process_token(t_shell *shell, t_simple_cmds *cmd, int *i);
void	free_simple_cmd(t_simple_cmds *cmd);
int add_redirection(t_simple_cmds *cmd, t_redir *redir);




#endif