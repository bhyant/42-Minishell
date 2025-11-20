/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:14:16 by asmati            #+#    #+#             */
/*   Updated: 2025/11/20 22:46:41 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Vérifie si la commande est un built-in (echo, cd, pwd, etc.)
int	is_builtin(char *cmd)
{
	 if (!cmd)
        return (0);
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", 6) == 0)
        return (1);
    if (ft_strncmp(cmd, "unset", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "exit", 4) == 0)
        return (1);
	return (0);

}

// Exécute un built-in en appelant la fonction correspondante
int	exec_builtin(char **args, t_shell *shell)
{
	if(ft_strncmp(args[0], "echo", 4) == 0)
        return (ft_echo(args));
	else if(ft_strncmp(args[0], "pwd", 3) == 0)
        return (ft_pwd(args));
	else if(ft_strncmp(args[0], "cd", 2) == 0)
        return (builtin_cd(shell, args));
	else if(ft_strncmp(args[0], "export", 6) == 0)
        return (ft_export(args, &shell->env));
	else if(ft_strncmp(args[0], "unset", 5) == 0)
        return (ft_unset(args, &shell->env));
	else if(ft_strncmp(args[0], "env", 3) == 0)
        return (ft_env(shell->env));
	else if(ft_strncmp(args[0], "exit", 4) == 0)
        return (ft_exit(args, shell));
	return (0);
}

// Trouve le chemin complet d'une commande dans le PATH
char *find_command_path(char *cmd, t_shell *shell)
{
	char **paths;
	char *full_path;
	char *temp;
	char *path_env;
	int i;

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
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_array(paths, -1), full_path);
		free(full_path);
		i++;
	}
	return (free_array(paths, -1), NULL);
}

// Exécute une commande externe avec fork + execve
int	exec_external(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path (args[0], shell);
	if (!cmd_path)
		return (ft_putstr_fd ("minishell: ", 2),
			ft_putstr_fd (args[0], 2)
			, ft_putstr_fd (": command not found\n", 2), 127);
	pid = fork();
	if (pid == -1)
		return (free (cmd_path), perror ("fork"), 1);
	if (pid == 0)
	{
		execve (cmd_path, args, shell->envp);
		perror ("execve");
		free (cmd_path);
		exit (1);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// Fonction principale : exécute une commande (builtin ou externe)
int	execute_command(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (exec_builtin(args, shell));
	return (exec_external(args, shell));
}