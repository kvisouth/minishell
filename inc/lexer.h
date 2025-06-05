/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevso <kevso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:07 by kevso             #+#    #+#             */
/*   Updated: 2025/06/05 13:28:49 by kevso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_lexer
{
	char	**tokens;
	int		token_count;
	char	*new_cmdline;
	bool	inside_quotes;
	char	quote_char;
}	t_lexer;

typedef struct s_shell	t_shell;

/* LEXER */
int		is_op(char c);
void	handle_quotes(char *cmdline, t_lexer *lex, int *i, int *j);
void	handle_operators(char *cmdline, t_lexer *lex, int *i, int *j);
void	initialize_lexer(t_lexer *lex, char *cmdline);
char	*add_spaces_to_cmdline(char *cmdline, t_lexer *lex);
int		count_tokens(char *str, t_lexer *lex);
char	**split_tokens(char *str, t_lexer *lex);
int		lexer(t_shell *shell);

#endif