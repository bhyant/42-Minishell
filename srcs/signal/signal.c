/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:57:26 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/30 15:27:31 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	shell_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = signal + 128;
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
