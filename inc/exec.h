/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:13:24 by kevso             #+#    #+#             */
/*   Updated: 2025/03/14 14:54:14 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../inc/minishell.h"

typedef struct s_shell t_shell;

int	add_path_to_cmd(t_shell *shell);
int	exec(t_shell *shell);
int	execute_command(t_shell *shell);

#endif