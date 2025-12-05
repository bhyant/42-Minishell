/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:04 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/04 22:39:53 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_shell *shell, char **args)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = env_get_value(shell->env, "HOME");
		if (!path)
		{
			ft_putendl_fd ("cd: HOME not set", 2);
			return (NULL);
		}
		return (path);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = env_get_value (shell->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd ("cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
		return (path);
	}
	return (args[1]);
}

static void	get_old_pwd(char *old_pwd, char *old_pwd_env)
{
	if (!getcwd(old_pwd, 1024))
	{
		if (old_pwd_env)
			ft_strlcpy(old_pwd, old_pwd_env, 1024);
		else
			old_pwd[0] = '\0';
	}
}

static int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (args[1] && args[2])
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	get_old_pwd(old_pwd, env_get_value(shell->env, "PWD"));
	path = get_path(shell, args);
	if (!path)
		return (1);
	if (change_directory(path))
		return (1);
	if (old_pwd[0])
		env_set(&shell->env, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)))
		env_set(&shell->env, "PWD", new_pwd);
	return (0);
}
