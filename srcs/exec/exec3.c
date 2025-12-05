/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/05 08:18:39 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = try_path(paths, cmd, i);
		if (full_path)
			return (free_array(paths, -1), full_path);
		i++;
	}
	return (free_array(paths, -1), NULL);
}

int	exec_pipeline(t_shell *shell)
{
	t_command	*cmd;
	int			pipefd[2];
	int			prev_fd;
	int			status;
	pid_t		last_pid;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->command;
	while (cmd)
	{
		if (process_heredocs(cmd, shell) == -1)
			return (shell->exit_code);
		if (cmd->next)
			pipe(pipefd);
		last_pid = fork();
		if (last_pid < 0)
			perror("fork");
		else if (last_pid == 0)
			handle_child(cmd, shell, pipefd, prev_fd);
		else
			handle_parent(pipefd, &prev_fd, cmd);
		cmd = cmd->next;
	}
	cmd = shell->command;
	while (cmd)
	{
		close_heredocs(cmd);
		cmd = cmd->next;
	}
	signal_selector(3);
	while (1)
	{
		pid_t	pid;

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
	return (shell->exit_code);
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char		**paths;
	char		*path_env;
	struct stat	st;

	shell->cmd_error_code = 127;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			return (ft_putstr_fd(cmd, 2),
				ft_putstr_fd(": No such file or directory\n", 2), NULL);
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
			return (shell->cmd_error_code = 126, ft_putstr_fd(cmd, 2),
				ft_putstr_fd(": Is a directory\n", 2), NULL);
		if (access(cmd, X_OK) == -1)
			return (shell->cmd_error_code = 126, ft_putstr_fd(cmd, 2),
				ft_putstr_fd(": Permission denied\n", 2), NULL);
		return (ft_strdup(cmd));
	}
	path_env = env_get_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
