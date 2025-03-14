///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   test_parser.c                                      :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2025/03/12 16:57:39 by abreuil           #+#    #+#             */
///*   Updated: 2025/03/14 15:06:37 by abreuil          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "../inc/minishell.h"

///* Print a redirection list for debugging */
//static void	print_redirects(t_redir *redirects)
//{
//    t_redir	*current;

//    current = redirects;
//    if (!current)
//        return ;
//    printf("  Redirections: ");
//    while (current)
//    {
//        if (current->type == REDIR_IN)
//            printf("< %s ", current->file);
//        else if (current->type == REDIR_OUT)
//            printf("> %s ", current->file);
//        else if (current->type == REDIR_APPEND)
//            printf(">> %s ", current->file);
//        else if (current->type == REDIR_HEREDOC)
//            printf("<< %s ", current->file);
//        current = current->next;
//    }
//    printf("\n");
//}

///* Print command details - enhanced version of print_commands */
//static void	print_cmd_details(t_simple_cmds *cmd, int index)
//{
//    int	i;

//    printf("Command %d: ", index);
//    if (cmd->builtin)
//        printf("[BUILTIN] ");
//    i = 0;
//    while (cmd->str && cmd->str[i])
//    {
//        printf("[%s] ", cmd->str[i]);
//        i++;
//    }
//    printf("\n");
//    print_redirects(cmd->redirects);
//}

///* Detailed print of command structure */
//static void	print_detailed_cmds(t_simple_cmds *cmds)
//{
//    t_simple_cmds	*current;
//    int				cmd_index;

//    current = cmds;
//    cmd_index = 0;
//    printf("\n===== PARSED COMMAND STRUCTURE =====\n");
//    while (current)
//    {
//        print_cmd_details(current, cmd_index++);
//        if (current->next)
//            printf("  | (pipe to next command)\n");
//        current = current->next;
//    }
//    printf("===================================\n\n");
//}

///* Run a single parser test with the given input */
//static void	run_parser_test(char *input, int test_num)
//{
//    t_shell	shell;

//    printf("Test %d: '%s'\n", test_num, input);
//    shell.cmdline = ft_strdup(input);
//    if (!shell.cmdline)
//    {
//        printf("Memory allocation failed\n");
//        return ;
//    }
    
//    if (!lexer(&shell))
//    {
//        printf("Lexer failed!\n\n");
//        free(shell.cmdline);
//        return ;
//    }
    
//    if (!parser(&shell))
//    {
//        printf("Parser failed!\n\n");
//        free(shell.cmdline);
//        free_tab(shell.lexer.tokens);
//        free(shell.new_cmdline);
//        return ;
//    }
    
//    print_detailed_cmds(shell.simple_cmds);
    
//    // Cleanup
//    free_simple_cmd(shell.simple_cmds);
//    free_tab(shell.lexer.tokens);
//    free(shell.new_cmdline);
//    free(shell.cmdline);
//    printf("\n");
//}

///* Test the parser with predefined test cases */
//void	test_parser(void)
//{
//    int	test_num;
    
//    test_num = 1;
    
//    // Simple commands
//    run_parser_test("ls -la", test_num++);
//    run_parser_test("echo hello world", test_num++);
    
//    // Commands with redirections
//    run_parser_test("ls > file.txt", test_num++);
//    run_parser_test("cat < input.txt", test_num++);
//    run_parser_test("echo hello >> output.txt", test_num++);
//    run_parser_test("cat << EOF", test_num++);
    
//    // Pipe commands
//    run_parser_test("ls | grep a", test_num++);
//    run_parser_test("cat file.txt | grep pattern | wc -l", test_num++);
    
//    // Complex commands
//    run_parser_test("cat < input.txt | grep pattern > output.txt", test_num++);
//    run_parser_test("echo hello > file1 | cat file2 | sort", test_num++);
//    run_parser_test("ls -la | grep .c > sources.txt", test_num++);
    
//    // Commands with builtin recognition
//    run_parser_test("echo test | cd /tmp", test_num++);
//    run_parser_test("export PATH=/usr/bin", test_num++);
//    run_parser_test("exit 0", test_num++);
    
//    // Edge cases
//    run_parser_test("ls > file1 > file2", test_num++);
//    run_parser_test("cat < input1 < input2", test_num++);
//}

///* Main function for parser test */
//int	main(void)
//{
//    printf("\n===== MINISHELL PARSER TEST =====\n\n");
//    test_parser();
//    printf("===== TEST COMPLETE =====\n\n");
//    return (0);
//}