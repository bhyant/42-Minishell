/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:00:00 by asmati            #+#    #+#             */
/*   Updated: 2025/12/07 21:09:51 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (redir->type == HEREDOC)
		fd = redir->heredoc_fd;
	else if (redir->type == IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -2;
	return (fd);
}

int	apply_redir_fd(t_redir *redir, int fd)
{
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	if (redir->type == IN || redir->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
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
