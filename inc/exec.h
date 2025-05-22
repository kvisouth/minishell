/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:24 by kevso             #+#    #+#             */
/*   Updated: 2025/05/22 18:33:41 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../inc/minishell.h"

typedef struct s_shell t_shell;

int	add_path_to_cmd(t_shell *shell, t_simple_cmds *cmd);
int	exec(t_shell *shell);
// int	execute_command(t_shell *shell, t_simple_cmds *cmd);

/* BUILT-IN */
int	    builtin_echo(char **args);
void	builtin_env(char **env);
void	builtin_pwd(void);
int     builtin_cd(t_shell *shell, t_simple_cmds *cmd);
int		builtin_unset(t_shell *shell, t_simple_cmds *cmd);
int 	builtin_export(t_shell *shell, t_simple_cmds *cmd);
void	builtin_exit(char **args);
char	**copy_envp(char **envp);

char		*expand_heredoc_line(char *line);

#endif