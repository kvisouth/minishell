/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nok <nok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:12 by kevso             #+#    #+#             */
/*   Updated: 2025/04/12 10:29:54 by nok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Executes the builtin command */
void	exec_builtin(t_shell *shell, t_simple_cmds *cmd)
{
	if (ft_strcmp(cmd->str[0], "env") == 0)
		builtin_env(shell->env);
	else if (ft_strcmp(cmd->str[0], "cd") == 0)
		builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->str[0], "echo") == 0)
		builtin_echo(cmd->str);
	else if (ft_strcmp(cmd->str[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->str[0], "export") == 0)
		builtin_export(shell, cmd);
	 else if (ft_strcmp(cmd->str[0], "unset") == 0)
	 	builtin_unset(shell, cmd);
	// else if (ft_strcmp(cmd->str[0], "exit") == 0)
	// 	builtin_exit(shell, cmd);
}

/* Returns 1 if the command does not have a path */
int	cmd_have_no_path(char *cmd)
{
	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.') || ft_strchr(cmd, '~'))
		return (0);
	return (1);
}

void	count_cmds(t_shell *shell)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = shell->simple_cmds;
	while (tmp)
	{
		i++;
		tmp->index = i;
		tmp = tmp->next;
	}
	shell->nb_cmds = i;
}

/*
Will add the path to every commands that does not have a path yet
*/
void	format_cmds(t_shell *shell)
{
	t_simple_cmds	*cmd;

	cmd = shell->simple_cmds;
	while (cmd)
	{
		if (cmd_have_no_path(cmd->str[0]))
		{
			if (!add_path_to_cmd(shell, cmd))
			{
				perror("add_path_to_cmd");
				return ;
			}
		}
		cmd = cmd->next;
	}
}

void	child_process(t_shell *shell, t_simple_cmds *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (cmd->pid == 0)
	{
		// for (int i = 0; cmd->str[i]; i++)
		// 	printf("cmd[%d]: %s\n", i, cmd->str[i]);
		if (execve(cmd->str[0], cmd->str, shell->env) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

void	execute_pipeline(t_shell *shell)
{
    int		pipefd[2];
    pid_t	pid;
    int		prev_fd = -1; // Pour stocker le côté lecture du pipe précédent
    t_simple_cmds *cmd = shell->simple_cmds;

    while (cmd)
    {
        if (cmd->next) // Si une commande suivante existe, créez un pipe
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0) // Processus enfant
        {
            if (prev_fd != -1) // Si un pipe précédent existe, redirigez STDIN
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmd->next) // Si un pipe suivant existe, redirigez STDOUT
            {
                close(pipefd[0]); // Fermez le côté lecture du pipe
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (cmd->builtin) // Exécutez une commande builtin
                exec_builtin(shell, cmd);
            else // Exécutez une commande externe
            {
                if (execve(cmd->str[0], cmd->str, shell->env) == -1)
                {
                    perror("execve");
                    exit(1);
                }
            }
        }

        // Processus parent
        if (prev_fd != -1) // Fermez le côté lecture du pipe précédent
            close(prev_fd);
        if (cmd->next) // Fermez le côté écriture du pipe actuel
            close(pipefd[1]);

        prev_fd = pipefd[0]; // Stockez le côté lecture pour la prochaine commande
        cmd = cmd->next; // Passez à la commande suivante
    }

    // Attendez tous les processus enfants
    while (wait(NULL) > 0);
}

/* Executes the command */
int	execute_command(t_shell *shell, t_simple_cmds *cmd)
{
	//printf("bool built-in: %d\n", cmd->builtin);
	if (!shell->simple_cmds->builtin)
	{
		child_process(shell, cmd);
	}
	else
	{
		exec_builtin(shell, cmd);
	}
	return (0);
}

int	exec(t_shell *shell)
{
	count_cmds(shell);
	format_cmds(shell);
	if (shell->nb_cmds > 1)
		execute_pipeline(shell);
	else
		execute_command(shell, shell->simple_cmds);
	wait(NULL);
	return (0);
}

/* Returns the exit status */
// int	exec(t_shell *shell)
// {
// 	count_cmds(shell);
// 	while (shell->simple_cmds)
// 	{
// 		if (shell->simple_cmds->builtin == false)
// 		{
// 			if (cmd_have_no_path(shell->simple_cmds->str[0]))
// 			{
// 				if (!add_path_to_cmd(shell))
// 					return (0);
// 			}
// 		}
// 		execute_command(shell, shell->simple_cmds);
// 		shell->simple_cmds = shell->simple_cmds->next;
// 	}
// 	wait(NULL);
// 	return (0);
// }

