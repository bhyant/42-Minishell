/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:57:26 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 13:45:20 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	shell_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal + 128;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
		g_signal = signal + 128;
}

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
		close(STDIN_FILENO);
	}
}

void	exec_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		g_signal = 131;
	}
}

void	signal_selector(int mode)
{
	if (mode == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, shell_signal);
	}
	else if (mode == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_signal);
	}
	else if (mode == 3)
	{
		signal(SIGQUIT, exec_signal);
		signal(SIGINT, exec_signal);
	}
}
