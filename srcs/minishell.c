/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:35:28 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_cleanup(t_shell *shell)
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

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	signal(SIGPIPE, SIG_IGN);
	if (isatty(STDIN_FILENO))
	{
		print_welcome_msg();
		print_welcome_msg2();
	}
	else
		return (ft_putstr_fd("Error : Minishell Need a TTY",
				STDERR_FILENO), 1);
	if (!init_shell(&shell, envp))
		return (ft_putstr_fd("Error : Failed to initialize shell",
				STDERR_FILENO), 1);
	loop_readline(&shell);
	shell_cleanup(&shell);
	return (shell.exit_code);
}
