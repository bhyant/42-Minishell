/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:00:00 by asmati            #+#    #+#             */
/*   Updated: 2025/12/11 23:59:21 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_parent(int pipefd[2], int *prev_fd, t_command *cmd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (0);
}

void	handle_command_not_found(char *cmd, t_shell *shell)
{
	if (shell->cmd_error_code == 127)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	exec_cmd_child(t_shell *shell, t_command *cmd)
{
	signal_selector(3);
	if (cmd->redir && apply_redirections(cmd->redir, shell) == -1)
	{
		shell_cleanup(shell);
		exit(1);
	}
	shell->exit_code = execute_command(cmd->args, shell);
	shell_cleanup(shell);
	exit(shell->exit_code);
}

int	exec_cmd_parent(t_command *cmd, int status)
{
	close_heredocs(cmd);
	signal_selector(3);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
