/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:23 by kevso             #+#    #+#             */
/*   Updated: 2025/05/27 22:15:14 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = 0;

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_simple_cmd_exec(t_simple_cmds *cmd)
{
	if (!cmd)
		return ;
	if (cmd->str)
		free_tab(cmd->str);
	if (cmd->redirects)
		free_redir(cmd->redirects);
	free(cmd);
}

void	free_minishell(t_shell *shell)
{
	t_simple_cmds	*tmp;

	free(shell->cmdline);
	free_tab(shell->lexer.tokens);
	free(shell->lexer.new_cmdline);
	while (shell->simple_cmds)
	{
		tmp = shell->simple_cmds->next;
		free_simple_cmd_exec(shell->simple_cmds);
		shell->simple_cmds = tmp;
	}
}

void	start_minishell(t_shell *shell)
{
	shell->end = false;
	if (!lexer(shell))
	{
		free(shell->lexer.new_cmdline);
		return (free(shell->cmdline));
	}
		if (!expand_tokens(shell))
	{
		free(shell->cmdline);
		free_tab(shell->lexer.tokens);
		return (free(shell->lexer.new_cmdline));
	}
	if (!validate_tokens(shell))
	{
		free(shell->cmdline);
		free_tab(shell->lexer.tokens);
		return (free(shell->lexer.new_cmdline));
	}
	if (!parser(shell))
	{
		return ;
	}
	if (!exec(shell))
		return (free_minishell(shell));
	free_minishell(shell);

}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	minishell_loop(t_shell *shell)
{
	char	*cmdline;

	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		cmdline = readline("minishell> ");
		if (!cmdline)
		{
			free_tab(shell->env);
			free(cmdline);
			rl_clear_history();
			break ;
		}
		add_history(cmdline);
		shell->cmdline = cmdline;
		start_minishell(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1 && av)
		return (1);
	shell.env = NULL;
	shell.env = init_shell_env(envp);
	if (!shell.env)
		return (1);
	minishell_loop(&shell);
	return (0);
}
