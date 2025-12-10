/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 11:45:10 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->token = NULL;
	shell->command = NULL;
	shell->envp = NULL;
	shell->entry = NULL;
	shell->exit_code = 0;
	shell->cmd_error_code = 0;
	shell->env = init_env(envp);
	if (!shell->env)
		return (false);
	return (true);
}

void    shell_cleanup(t_shell *shell)
{
    if (shell->env)
        free_env(shell->env);
    if (shell->envp)
        free_envp(shell->envp);
    if (shell->token)
        ft_tokenclear(&shell->token);
    if (shell->command)
        free_command(shell->command);
    if (shell->entry)
    {
        free(shell->entry);
        shell->entry = NULL;
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void    loop_readline(t_shell *shell) 
{
    while (1)
    {
        g_signal = 0;
        signal_selector(1);
        shell->entry = readline("🖕$> ");
        if (!shell->entry)
        {
            printf("exit\n");
            break ;
        }
        if (g_signal == 130)
            shell->exit_code = 130;
        if (shell->entry[0] != '\0')
            add_history(shell->entry);
        if (!parsing(shell->entry, shell))
        {
            shell->exit_code = 2;
            free(shell->entry);
            shell->entry = NULL;
            continue ;
        }
        else
            execute_and_cleanup(shell);
        cleanup_iteration(shell);
        if (shell->entry)
        {
            free(shell->entry);
            shell->entry = NULL;
        }
    }
}

void print_welcome_msg(void)
{
    printf(BOLDMAGENTA);
    printf("███╗   ███╗██╗███╗   ██╗██╗     ██████╗██╗  ██╗██╗███████╗███╗   ██╗███╗   ██╗███████╗    \n");
    printf("████╗ ████║██║████╗  ██║██║    ██╔════╝██║  ██║██║██╔════╝████╗  ██║████╗  ██║██╔════╝    \n");
    printf("██╔████╔██║██║██╔██╗ ██║██║    ██║     ███████║██║█████╗  ██╔██╗ ██║██╔██╗ ██║█████╗      \n");
    printf("██║╚██╔╝██║██║██║╚██╗██║██║    ██║     ██╔══██║██║██╔══╝  ██║╚██╗██║██║╚██╗██║██╔══╝      \n");
    printf("██║ ╚═╝ ██║██║██║ ╚████║██║    ╚██████╗██║  ██║██║███████╗██║ ╚████║██║ ╚████║███████╗    \n");
    printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝    \n");
    printf("\n");
    printf(RESET);
    printf(CYAN "    Welcome to MINISHELL v1.0\n" RESET);
    printf(CYAN "    Created by: [asmati & bhyant]\n\n" RESET);
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;

    (void)ac;
    (void)av;
    signal(SIGPIPE, SIG_IGN);
	print_welcome_msg();
    if (!init_shell(&shell, envp))
        return (ft_putstr_fd("Error : Failed to initialize shell",
                STDERR_FILENO), 1);
                
    loop_readline(&shell);
    shell_cleanup(&shell);
    return (shell.exit_code);
}
