/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:19:23 by kevso             #+#    #+#             */
/*   Updated: 2025/06/05 13:23:15 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = 0;

void	start_minishell(t_shell *shell)
{
	shell->end = false;
	if (!lexer(shell))
	{
		free(shell->lexer.new_cmdline);
		shell->lexer.new_cmdline = NULL;
		free_tab(shell->lexer.tokens);
		shell->lexer.tokens = NULL;
		free(shell->cmdline);
		shell->cmdline = NULL;
		return ;
	}
	if (!expand_tokens(shell))
	{
		free_expander(shell);
		return ;
	}
	if (!parser(shell))
	{
		free_minishell(shell);
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
	init_shell_struct(&shell);
	shell.env = NULL;
	shell.env = init_shell_env(envp);
	if (!shell.env)
		return (1);
	minishell_loop(&shell);
	return (0);
}
