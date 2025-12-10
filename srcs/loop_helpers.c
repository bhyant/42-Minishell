/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 05:51:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:35:29 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_empty_entry(t_shell *shell)
{
	if (!shell->entry)
	{
		printf("exit\n");
		return (0);
	}
	return (1);
}

static void	handle_parsing_error(t_shell *shell)
{
	shell->exit_code = 2;
	free(shell->entry);
	shell->entry = NULL;
}

static void	process_entry(t_shell *shell)
{
	if (g_signal == 130)
		shell->exit_code = 130;
	if (shell->entry[0] != '\0')
		add_history(shell->entry);
	if (!parsing(shell->entry, shell))
		handle_parsing_error(shell);
	else
		execute_and_cleanup(shell);
}

void	loop_readline(t_shell *shell)
{
	char	*prompt_str;

	while (1)
	{
		g_signal = 0;
		signal_selector(1);
		prompt_str = get_prompt(shell);
		shell->entry = readline(prompt_str);
		free(prompt_str);
		if (!handle_empty_entry(shell))
			break ;
		process_entry(shell);
		cleanup_iteration(shell);
		if (shell->entry)
		{
			free(shell->entry);
			shell->entry = NULL;
		}
	}
}
