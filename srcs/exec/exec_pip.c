/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:12:31 by asmati            #+#    #+#             */
/*   Updated: 2025/12/10 11:42:42 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static pid_t	fork_pipeline_cmd(t_command *cmd, t_shell *shell, int pipefd[2],
		int *prev_fd)
{
	pid_t	pid;

	if (process_heredocs(cmd, shell) == -1)
	{
		close_all_heredocs(shell);
		return (-2);
	}
	if (cmd->next)
		pipe(pipefd);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
		handle_child(cmd, shell, pipefd, *prev_fd);
	else
		handle_parent(pipefd, prev_fd, cmd);
	return (pid);
}

static void	wait_pipeline(pid_t last_pid, t_shell *shell)
{
	pid_t	pid;
	int		status;

	signal_selector(3);
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status))
				shell->exit_code = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else
				shell->exit_code = 1;
		}
	}
}

int	exec_pipeline(t_shell *shell)
{
	t_command	*cmd;
	int			pipefd[2];
	int			prev_fd;
	pid_t		last_pid;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->command;
	while (cmd)
	{
		last_pid = fork_pipeline_cmd(cmd, shell, pipefd, &prev_fd);
		if (last_pid == -2)
		{
			if (prev_fd != -1)
				close(prev_fd);
			close_all_heredocs(shell);
			return (shell->exit_code);
		}
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		(close(prev_fd), prev_fd = -1);
	close_all_heredocs(shell);
	wait_pipeline(last_pid, shell);
	return (shell->exit_code);
}

int	exec_commands(t_shell *shell)
{
	if (!shell->command)
		return (0);
	if (!shell->command->next)
		return (exec_cmd(shell, shell->command));
	return (exec_pipeline(shell));
}