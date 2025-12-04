/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:55 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/04 21:30:29 by asmati           ###   ########.fr       */
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

static void	handle_no_args(t_shell *shell)
{
	shell_cleanup(shell);
	exit(shell->exit_code);
}

static void	handle_non_numeric(char *arg, t_shell *shell)
{
	ft_putstr_fd ("minishell: exit: ", 2);
	ft_putstr_fd (arg, 2);
	ft_putendl_fd (": numeric argument required", 2);
	shell_cleanup(shell);
	exit (2);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd ("exit", 1);
	if (!args[1])
		handle_no_args(shell);
	if (!is_numeric (args[1]))
		handle_non_numeric(args[1], shell);
	if (args[2])
	{
		ft_putendl_fd ("minishell: exit: too many arguments", 2);
		shell->exit_code = 1;
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit_code = ((exit_code % 256) + 256) % 256;
	shell_cleanup(shell);
	exit(exit_code);
}
