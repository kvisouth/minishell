/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:43 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 14:01:22 by kevso            ###   ########.fr       */
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
# include <stddef.h>
# include "../libft/libft.h"
# include "parser.h"
# include "lexer.h"
# include "exec.h"
# include "expander.h"

extern int	g_sig; // Global variable to store the exit status

typedef struct s_shell
{
	bool			end;
	char			**env;
	char			*cmdline;
	char			*new_cmdline;
	int				nb_cmds;
	char			*path;
	int				pipefd[2];
	int				heredoc_flag;
	t_lexer			lexer;
	t_simple_cmds	*simple_cmds;
	t_parser		parser;
}	t_shell;

char	**init_shell_env(char **envp);
void	sig_handler(int sig);
void	free_redir(t_redir *redir);
void	free_simple_cmd_exec(t_simple_cmds *cmd);
void	free_minishell(t_shell *shell);
void	init_shell_struct(t_shell *shell);

#endif