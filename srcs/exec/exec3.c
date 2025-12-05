/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:18:20 by asmati            #+#    #+#             */
/*   Updated: 2025/12/04 21:14:13 by asmati           ###   ########.fr       */
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

static void	process_pipeline_cmd(t_command *cmd, t_shell *shell, int pipefd[2],
		int *prev_fd)
{
	pid_t	pid;

	if (cmd->next)
		pipe(pipefd);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
		handle_child(cmd, shell, pipefd, *prev_fd);
	else
		handle_parent(pipefd, prev_fd, cmd);
}

int	exec_pipeline(t_shell *shell)
{
	t_command	*cmd;
	int			pipefd[2];
	int			prev_fd;
	int			status;

	prev_fd = -1;
	cmd = shell->command;
	while (cmd)
	{
		if (process_heredocs(cmd, shell) == -1)
			return (1);
		process_pipeline_cmd(cmd, shell, pipefd, &prev_fd);
		cmd = cmd->next;
	}
	cmd = shell->command;
	while (cmd)
	{
		close_heredocs(cmd);
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (shell->exit_code);
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = env_get_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
