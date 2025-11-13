/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/14 00:39:18 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_readline(t_shell *shell, char *entry)
{
	while (1)
	{
		signal_handler();
		shell->token = NULL;
		entry = readline("🖕> ");
		if (!entry)
			break ;
		else
		{
			add_history(entry);
		}
		if (!parsing(entry, &shell))
			continue ;
		
	}
}

int main(int ac, char **av, char **envp)
{
	(void)envp;
	char	*entry;
	t_shell	shell;
	
	(void)ac;
	(void)av;
	entry = NULL;
	if (!isatty(0))
		return(printf("Error : MINISHELL Need a tty"), 1);
	// Initier l'Env
	loop_readline(&shell, entry);
	// Clear l'env a la fin de l'exec du code
	return (0);
}