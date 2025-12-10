/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:09:49 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:09:53 by tbhuiyan         ###   ########.fr       */
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

char	*try_path(char **paths, char *cmd, int i)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(paths[i], "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
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
