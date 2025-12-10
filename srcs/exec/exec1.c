/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/10 01:01:04 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	exec_cmd(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (process_heredocs(cmd, shell) == -1)
		return (shell->exit_code);
	if (is_builtin(cmd->args[0]) && !cmd->redir)
		return (exec_builtin(cmd->args, shell));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_cmd_child(shell, cmd);
	waitpid(pid, &status, 0);
	return (exec_cmd_parent(cmd, status));
}

int	exec_commands(t_shell *shell)
{
	if (!shell->command)
		return (0);
	if (!shell->command->next)
		return (exec_cmd(shell, shell->command));
	return (exec_pipeline(shell));
}

void	close_all(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
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
