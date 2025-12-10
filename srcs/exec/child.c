/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/10 11:55:35 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child_process(char **args, char *cmd_path, t_shell *shell)
{
	execve(cmd_path, args, shell->envp);
	perror(args[0]);
	free(cmd_path);
	shell_cleanup(shell);
	exit(126);
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

void	handle_child(t_command *cmd, t_shell *shell, int pipefd[2], int prev_fd)
{
	signal_selector(3);
	if (prev_fd != -1)
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
	if (cmd->next)
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