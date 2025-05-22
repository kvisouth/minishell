/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:49:47 by abreuil           #+#    #+#             */
/*   Updated: 2025/05/22 19:45:08 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"
typedef struct s_expand
{
	int		start_pos;
	int		end_pos;
	int		in_quotes;
	char	*expanded;
	char	*var_name;
	char	*var_value;
	
	
}	t_expand;

/* Main functions */
int			expand_tokens(t_shell *shell);
char		*expand_token(char *token, char **env);

/* Helper functions */
char		*find_next_variable(char *str, t_expand *exp);
char		*expand_variable(char *var_name, char **env);
int			is_valid_var_char(char c, int first_char);
int			should_expand_in_quotes(char *token, int pos, t_expand *exp);
char		*replace_variable(char *token, t_expand *exp);
void		init_expand(t_expand *exp);
char		*remove_quotes(char *str);
#endif