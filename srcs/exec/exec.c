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

int	exec_external(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(args[0], shell);
	if (!cmd_path)
	{
		if (shell->cmd_error_code == 127)
			ft_putstr_fd(args[0], 2), ft_putstr_fd(": command not found\n", 2);
		return (shell->cmd_error_code);
	}
	pid = fork();
	if (pid == -1)
		return (free(cmd_path), perror("fork"), 1);
	if (pid == 0)
	{
		execve(cmd_path, args, shell->envp);
		perror(args[0]);
		free(cmd_path);
		shell_cleanup(shell);
		exit(126);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_command(char **args, t_shell *shell)
{
	if (!args || !args[0] || args[0][0] == '\0')
		return (0);
	if (is_builtin(args[0]))
		return (exec_builtin(args, shell));
	return (exec_external(args, shell));
}
