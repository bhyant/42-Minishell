/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:11:15 by asmati            #+#    #+#             */
/*   Updated: 2025/12/10 11:58:01 by asmati           ###   ########.fr       */
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

int	exec_external(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(args[0], shell);
	if (!cmd_path)
	{
		handle_command_not_found(args[0], shell);
		return (shell->cmd_error_code);
	}
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_child_process(args, cmd_path, shell);
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


