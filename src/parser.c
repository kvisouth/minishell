/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:07:48 by kevso             #+#    #+#             */
/*   Updated: 2025/03/10 17:54:56 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"

///* initializing parser */
//static void initialize_parser(t_shell *shell)
//{
//	shell->parser.tokens = shell->lexer.tokens;
//	shell->parser.token_index = 0;
//	shell->parser.token_count = shell->lexer.token_count;
//	shell->cmd = NULL;
//}

///* count arguments excluding redirections */
//void	count_arguments(t_shell *shell, int arg_count, char *token)
//{
//	while((token = peek_token(shell)) && !is_pipe(tokenm))
//	{
//		if (is_redirection(token))
//		{
//			next_token(shell);
//			next_token(shell);
//		}
//		else
//		{
//			arg_count++;
//			next_token(shell);
//		}
//	}
//}

///* Parse a simple command (command with arguments) */
//t_cmd	*parse_simple_command(t_shell *shell)
//{
//	t_cmd	*cmd;
//	char	*token;
//	int		arg_count;
//	int		i;
//	int		tmp_index;

//	arg_count = 0;
//	i = 0;
//	tmp_index = shell->parser.token_index;
//	if (!(cmd = malloc(sizeof(t_cmd))))
//		return (NULL);
//	cmd->type = CMD_SIMPLE;
//	cmd->redirects = NULL;
//	cmd->left = NULL;
//	cmd->right = NULL;
//	count_arguments(shell, arg_count, char *token);
//}
//t_cmd	*parse_pipeline(t_shell *shell)
//{
//	t_cmd	*left;
//	t_cmd	*right;
//	char	*token;
	
//	left = parse_simple_command(shell);
//	if (!left)
//		return (NULL);
//}
//t_cmd	*parse_command(t_shell *shell)
//{
//	return (parse_pipeline(shell));
//}

///* main parsing function*/
//int	parser(t_shell *shell)
//{
//	initialize_parser(shell);
//	shell -> cmd = parse_command(shell);
//	return (shell->cmd != NULL);
//}