/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/15 21:01:23 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->token = NULL;
	shell->command = NULL;
	shell->envp = NULL;
	shell->exit_code = 0;
	shell->env = init_env(envp);
	if (!shell->env)
		return (false);
	return (true);
}

static void	shell_cleanup(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->token)
		ft_tokenclear(&shell->token);
	if (shell->command)
		free_command(shell->command);
}

void	loop_readline(t_shell *shell, char *entry)
{
	while (1)
	{
		signal_selector(1);
		entry = readline("🖕$> ");
		if (g_signal != 0)
		{
			shell->exit_code = g_signal;
			g_signal = 0;
		}
		if (!entry)
		{
			printf("exit\n");
			break ;
		}
		else
			add_history(entry);
		if (!parsing(entry, shell))
		{
			free(entry);
			continue ;
		}
		else
		{
			shell->envp = create_env(shell->env);
			// EXEC ici
			if (shell->envp)
				free_envp(shell->envp);
			shell->envp = NULL;
		}
		if (shell->token)
			ft_tokenclear(&shell->token);
		if (shell->command)
			free_command(shell->command);
		free(entry);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*entry;
	t_shell	shell;

	(void)ac;
	(void)av;
	entry = NULL;
	if (!isatty(0))
		return (printf("Error : MINISHELL Need a tty"), 1);
	if (!init_shell(&shell, envp))
		return (ft_putstr_fd("Error : Failed to initialize shell", STDERR_FILENO), 1);
	loop_readline(&shell, entry);
	shell_cleanup(&shell);
	return (0);
}
