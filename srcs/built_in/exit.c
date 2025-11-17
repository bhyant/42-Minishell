/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:55 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:48 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd ("exit", 1);
	if (!args[1])
		exit(shell->exit_code);
	if (!is_numeric (args[1]))
	{
		ft_putstr_fd ("minishell: exit: ", 2);
		ft_putstr_fd (args[1], 2);
		ft_putendl_fd (": numeric argument required", 2);
		exit (2);
	}
	if (args[2])
	{
		ft_putendl_fd ("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
