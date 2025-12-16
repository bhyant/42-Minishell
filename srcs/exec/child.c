/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/16 21:18:42 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_child_01(t_shell *shell, int pipefd[2])
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 next");
		close(pipefd[0]);
		close(pipefd[1]);
		shell_cleanup(shell);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}
static void	handle_child_02(t_command *cmd, t_shell *shell, int pipefd[2],
		int prev_fd)
{
	if (dup2(prev_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 prev");
		close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		shell_cleanup(shell);
		exit(1);
	}
	close(prev_fd);
}

static void	exec_pipe_external(t_command *cmd, t_shell *shell)
{
	char	*cmd_path;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		shell_cleanup(shell);
		exit(0);
	}
	cmd_path = find_command_path(cmd->args[0], shell);
	if (!cmd_path)
	{
		handle_command_not_found(cmd->args[0], shell);
		shell_cleanup(shell);
		exit(shell->cmd_error_code);
	}
	exec_child_process(cmd->args, cmd_path, shell);
}

void	handle_child(t_command *cmd, t_shell *shell, int pipefd[2],
		int *prev_fd)
{
	signal_selector(3);
	if (*prev_fd != -1)
		handle_child_02(cmd, shell, pipefd, *prev_fd);
	if (cmd->next)
		handle_child_01(shell, pipefd);
	if (cmd->redir && apply_redirections(cmd->redir, shell) == -1)
	{
		shell_cleanup(shell);
		exit(1);
	}
	close_all_heredocs(shell);
	if (is_builtin(cmd->args[0]))
	{
		shell->exit_code = exec_builtin(cmd->args, shell);
		shell_cleanup(shell);
		exit(shell->exit_code);
	}
	else
	{
		exec_pipe_external(cmd, shell);
	}
}
