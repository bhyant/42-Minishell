/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:51:47 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/18 00:11:40 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_1(char *arg)
{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		return ;
}
static void error_2(void)
{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return ;
}
int	ft_pwd(char **args)
{
	char	*pwd;
	int		i;

	(void)args;
	i = 1;
	while (args && args[i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			if (args[i][1] == 'P' || args[i][1] == 'L')
			{
				i++;
				continue;
			}
			else
				return (error_1(args[i]), 2);
		}
		i++;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_2(), 1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
