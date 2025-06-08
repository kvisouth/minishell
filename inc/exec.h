/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:24 by kevso             #+#    #+#             */
/*   Updated: 2025/06/08 18:40:06 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../inc/minishell.h"

typedef struct s_shell	t_shell;

int		add_path_to_cmd(t_shell *shell, t_simple_cmds *cmd);
int		exec(t_shell *shell);

/* BUILT-IN */
void	exec_builtin(t_shell *shell, t_simple_cmds *cmd);
void	execute_builtin(t_shell *shell, t_simple_cmds *cmd);
int		builtin_echo(char **args);
void	builtin_env(char **env);
void	builtin_pwd(void);
int		builtin_cd(t_shell *shell, t_simple_cmds *cmd);
int		builtin_unset(t_shell *shell, t_simple_cmds *cmd);
int		builtin_export(t_shell *shell, t_simple_cmds *cmd);
void	builtin_exit(char **args);
char	**copy_envp(char **envp);
int		handle_redirections_bltn(t_simple_cmds *cmd);

/* UTILS */
void	count_cmds(t_shell *shell);
void	end(int code, bool kill, char *msg);
void	format_cmds(t_shell *shell);

/* COMMAND EXECUTION */
void	execute_command(t_shell *shell, t_simple_cmds *cmd);
void	wait_for_command(void);
void	setup_pipes(t_simple_cmds *cmd, int pipefd[2]);
void	handle_child_process(t_shell *shell,
			t_simple_cmds *cmd, int prev_fd, int pipefd[2]);

/* HEREDOC */
int		process_all_heredocs(t_shell *shell);
char	*expand_heredoc_line(char *line, char **env);

/* PIPES EXECUTION */
void	execute_pipeline(t_shell *shell);

/* REDIRECTIONS */
void	handle_redirections(t_simple_cmds *cmd);

/* SIGNALS */
void	set_signals_for_child(void);
void	reset_signals_for_parent(void);
void	set_signals_for_parent_with_children(void);

#endif