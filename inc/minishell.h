/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:43 by kevso             #+#    #+#             */
/*   Updated: 2025/03/14 14:54:07 by kevso            ###   ########.fr       */
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
# include "parser.h"
# include "lexer.h"
# include "exec.h"

typedef struct s_shell
{
	bool	end;
	char	**env;
	char	*cmdline;
	char	*new_cmdline;
	int		nb_cmds;
	char	*path;
	int		pipefd[2];
	t_lexer	lexer;
	t_simple_cmds	*simple_cmds;
    t_parser        parser;         // Parser state
}	t_shell;

char	**init_shell_env(char **envp);

#endif