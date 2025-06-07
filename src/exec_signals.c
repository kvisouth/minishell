/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:10:44 by kevso             #+#    #+#             */
/*   Updated: 2025/06/06 15:50:43 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Signal handler for SIGINT and SIGQUIT that ignores the signals
when the parent process has children.
*/
void	set_signals_for_parent_with_children(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
Signal handler for SIGINT and SIGQUIT that allows the parent process
to handle the signals normally, while ignoring them in the child process.
*/
void	reset_signals_for_parent(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
Signal handler for SIGINT and SIGQUIT that allows the child process
to handle the signals normally, while ignoring them in the parent process.
*/
void	set_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
