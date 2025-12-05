/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/12/02 16:50:39 by asmati            #+#    #+#             */
/*   Updated: 2025/12/02 16:50:39 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->args[0]) && !cmd->redir)
		return (exec_builtin(cmd->args, shell));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal_selector(4);
		if (cmd->redir)
			apply_redirections(cmd->redir, shell);
		execute_command(cmd->args, shell);
		exit(shell->exit_code);
	}
	signal_selector(3);
	waitpid(pid, &status, 0);
	signal_selector(1);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_commands(t_shell *shell)
{
	t_command	*cmd;
	int			pipefd[2];
	pid_t		pid;
	int			prev_fd;
	int			status;

	(1 && (prev_fd = -1, cmd = shell->command));
	if (!cmd)
		return (0);
	if (!cmd->next)
		return (exec_cmd(shell, cmd));
	while (cmd)
	{
		(cmd->next && pipe(pipefd));
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if(pid == 0)
		{
		signal_selector(4);
		if(cmd->redir)
			apply_redirections(cmd->redir, shell);
		execute_command(cmd->args, shell);
		shell_cleanup(shell);
		exit(shell->exit_code);
		}
		signal_selector(3);
		waitpid(pid, &status, 0);
		signal_selector(1);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				printf("\n");
			return (128 + WTERMSIG(status));
		}
		if (WIFEXITED(status))
      	  return (WEXITSTATUS(status));
   		 return (1);
	}
	while(cmd)
	{
		if(cmd->next)
			pipe(pipefd);
		pid = fork();
		if(pid < 0)
			return(perror("fork"), 1);
		else if(pid == 0)
		{
			signal_selector(4);
			handle_child(cmd, shell, pipefd, prev_fd);
		}
		else
			handle_parent(pipefd, &prev_fd, cmd);
		cmd = cmd->next;
	}
	signal_selector(3);
	while (wait(NULL) > 0)
		;
	signal_selector(1);
	return (shell->exit_code);
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
	execute_command(cmd->args, shell);
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

	while (redir)
	{
		if (redir->type == HEREDOC)
			fd = handle_heredoc(redir->file, shell);
		else if (redir->type == IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (-1);
		if (redir->type == IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
