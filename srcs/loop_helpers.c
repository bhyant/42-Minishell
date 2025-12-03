/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 05:51:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/03 05:50:53 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
