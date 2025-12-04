/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:04 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/04 14:11:51 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_shell *shell, char **args)
{
	char	*path;

	if (!args[1] || ft_strncmp (args[1], "~", 2) == 0)
	{
		path = env_get_value(shell->env, "HOME");
		if (!path)
			ft_putendl_fd ("cd: HOME not set", 2);
		return (path);
	}
	if (strncmp (args[1], "-", 2) == 0)
	{
		path = env_get_value (shell->env, "OLDPWD");
		if (!path)
			ft_putendl_fd ("cd: OLDPWD not set", 2);
		return (path);
	}
	return (args[1]);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (!getcwd (old_pwd, sizeof(old_pwd)))
		return (1);
	path = get_path(shell, args);
	if (!path)
		return (1);
	if (chdir (path) == -1)
	{
		ft_putstr_fd ("cd: ", 2);
		ft_putstr_fd (path, 2);
		ft_putendl_fd (": No such file or directory", 2);
		return (1);
	}
	env_set (&shell->env, "OLDPWD", old_pwd);
	if (getcwd (new_pwd, sizeof(new_pwd)))
		env_set (&shell->env, "PWD", new_pwd);
	return (0);
}
