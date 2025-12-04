/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/04 20:18:20 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (process_heredocs(cmd, shell) == -1)
		return (1);
	if (is_builtin(cmd->args[0]) && !cmd->redir)
		return (exec_builtin(cmd->args, shell));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (cmd->redir)
			apply_redirections(cmd->redir, shell);
		shell->exit_code = execute_command(cmd->args, shell);
		shell_cleanup(shell);
		exit(shell->exit_code);
	}
	close_heredocs(cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_commands(t_shell *shell)
{
	if (!shell->command)
		return (0);
	if (!shell->command->next)
		return (exec_cmd(shell, shell->command));
	return (exec_pipeline(shell));
}

void	handle_child(t_command *cmd, t_shell *shell, int pipefd[2],
		int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->redir)
		apply_redirections(cmd->redir, shell);
	shell->exit_code = execute_command(cmd->args, shell);
	shell_cleanup(shell);
	exit(shell->exit_code);
}

int	handle_parent(int pipefd[2], int *prev_fd, t_command *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (0);
}

int	apply_redirections(t_redir *redir, t_shell *shell)
{
	int	fd;

	(void)shell;
	while (redir)
	{
		fd = open_redir_file(redir);
		if (fd == -2)
		{
			redir = redir->next;
			continue ;
		}
		if (apply_redir_fd(redir, fd) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
