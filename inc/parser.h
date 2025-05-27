/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:19:02 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/27 12:46:54 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../inc/lexer.h"
# include "../inc/minishell.h"
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/* Command types */
typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_REDIR
}							t_cmd_type;

/* Redirection types */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
}							t_redir_type;

/* Redirection structure */
typedef struct s_redir
{
	t_redir_type			type;
	char					*file;
	char					*heredoc_file;
	struct s_redir			*next;
}				t_redir;

// command structure with arguments
typedef struct s_simple_cmds
{
	int						index;
	char					**str;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
	t_redir					*redirects;
	pid_t					pid;
	bool					builtin;
}				t_simple_cmds;

/* Parser structure */
typedef struct s_parser
{
	char	**tokens;
	int		token_index;
	int		token_count;
}				t_parser;

/* Token validation */
int				validate_tokens_for_parser(t_shell *shell);
int				validate_tokens(t_shell *shell);
char			*peek_token(t_shell *shell);
char			*next_token(t_shell *shell);
int				check_consecutive_ops(char *curr_token, char *next_token);
int				handle_operator(t_shell *shell, int token_count, int i);
int				handle_no_redirect(t_shell *shell, int token_count,
					int i, int *skip);
int				handle_empty_command_between_pipe(t_shell *shell,
					int token_count, int i);
int				handle_pipe(t_shell *shell, int token_count);

/* Function prototypes for parser */
t_redir			*parse_redirection(t_shell *shell);
t_simple_cmds	*handle_redirection(t_simple_cmds *cmd, t_shell *shell);
void			fill_arguments(t_simple_cmds *cmd, t_shell *shell);
t_simple_cmds	*parse_simple_cmd(t_shell *shell);
t_simple_cmds	*parse_pipeline(t_shell *shell);
int				parser(t_shell *shell);
t_simple_cmds	*create_simple_cmd(void);
t_simple_cmds	*alloc_cmd_args(t_simple_cmds *cmd, int word_count);

// test functions
void			print_commands(t_simple_cmds *cmds);
void			test_parser(void);
void			init_shell(t_shell *shell);
void			free_shell(t_shell *shell);
int				tokenize(t_shell *shell, char *input);

// parser_utils.c
int				is_redirection(char *token);
int				is_pipe(char *token);
int				is_operator(char *token);
int				ft_strcmp(const char *s1, const char *s2);
void			check_if_builtin(t_simple_cmds *cmd);
int				count_words(t_shell *shell);
int				add_argument(t_simple_cmds *cmd, char *word, int i);
int				process_token(t_shell *shell, t_simple_cmds *cmd, int *i);
void			free_simple_cmd(t_simple_cmds *cmd);
int				add_redirection(t_simple_cmds *cmd, t_redir *redir);
void			free_redirections(t_redir *redir);
t_redir			*init_redirection(t_redir_type type, char *file);
t_redir_type	get_redir_type(char *token);
int				get_redirection_tokens(t_shell *shell,
					char **token, char **target);
t_redir			*create_redirection(char *token, char *target);
t_simple_cmds	*prepare_simple_cmd(t_shell *shell, int *word_count);
t_simple_cmds	*process_simple_cmd(t_shell *shell,
					t_simple_cmds *cmd, int word_count);

#endif