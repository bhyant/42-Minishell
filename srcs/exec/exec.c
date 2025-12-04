/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:11:15 by asmati            #+#    #+#             */
/*   Updated: 2025/12/02 21:11:15 by asmati           ###   ########.fr       */
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

int	exec_builtin(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(shell, args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, &shell->env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, &shell->env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(shell->env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, shell));
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

char	*find_command_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = env_get_value(shell->env, "PATH");
	if (!path_env || !(paths = ft_split(path_env, ':')))
		return (NULL);
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

int	exec_external(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(args[0], shell);
	if (!cmd_path)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(args[0], 2),
			ft_putstr_fd(": command not found\n", 2), 127);
	pid = fork();
	if (pid == -1)
		return (free(cmd_path), perror("fork"), 1);
	if (pid == 0)
	{
		execve(cmd_path, args, shell->envp);
		perror("execve");
		free(cmd_path);
		shell_cleanup(shell);
		exit(1);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_command(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (exec_builtin(args, shell));
	return (exec_external(args, shell));
}
