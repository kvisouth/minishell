/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:43 by kevso             #+#    #+#             */
/*   Updated: 2025/03/07 15:34:45 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
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
# include "../libft/libft.h"


typedef struct s_lexer
{
	char	**tokens;
	int		token_count;
	char	*new_cmdline;
	bool	inside_quotes;
	char	quote_char;
}	t_lexer;

typedef struct s_shell
{
	bool	end;
	char	**env;
	char	*cmdline;
	char	*new_cmdline;
	t_lexer	lexer;
}	t_shell;


char	**init_shell_env(char **envp);

/* LEXER */
int		is_op(char c);
void	handle_quotes(char *cmdline, t_lexer *lex, int *i, int *j);
void	handle_operators(char *cmdline, t_lexer *lex, int *i, int *j);
void	initialize_lexer(t_lexer *lex, char *cmdline);
char	*add_spaces_to_cmdline(char *cmdline, t_lexer *lex);
int		lexer(t_shell *shell);

#endif