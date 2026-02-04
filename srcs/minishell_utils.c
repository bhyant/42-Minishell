/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:10:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2026/02/04 15:29:06 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	init_shell(t_shell *shell, char **envp)
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

void	print_welcome_msg(void)
{
	printf(BOLDMAGENTA);
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗");
	printf("██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝");
	printf("██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ");
	printf("██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ");
	printf("██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗");
	printf("███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝");
	printf("╚══════╝╚══════╝\n");
	printf("\n");
	printf(RESET);
	printf(CYAN "    Welcome to MINISHELL v1.0\n" RESET);
	printf(CYAN "    Created by: [asmati & bhyant]\n\n" RESET);
}

void	print_welcome_msg2(void)
{
	int	seed;

	seed = (long)&seed % 3;
	if (seed == 0)
		printf(BOLDGREEN "🚀 Minishell Ready!\n" RESET);
	else if (seed == 1)
		printf(BOLDMAGENTA "🔮 Welcome back, Master.\n" RESET);
	else
		printf(BOLDCYAN "💀 System online.\n" RESET);
}

void	execute_and_cleanup(t_shell *shell)
{
	shell->envp = create_env(shell->env);
	shell->exit_code = exec_commands(shell);
	if (shell->envp)
		free_envp(shell->envp);
	shell->envp = NULL;
}

void	cleanup_iteration(t_shell *shell)
{
	if (shell->token)
	{
		ft_tokenclear(&shell->token);
		shell->token = NULL;
	}
	if (shell->command)
	{
		free_command(shell->command);
		shell->command = NULL;
	}
}
