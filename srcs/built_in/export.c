/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/02 20:53:55 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export_without_args(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

void	split_key_value(char *arg, char **key, char **value, char **eq)
{
	*eq = ft_strchr(arg, '=');
	if (*eq)
	{
		**eq = '\0';
		*key = arg;
		*value = *eq + 1;
	}
	else
	{
		*key = arg;
		*value = "";
	}
}

int	process_export_arg(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	split_key_value(arg, &key, &value, &equal_sign);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		if (equal_sign)
			*equal_sign = '=';
		return (1);
	}
	env_set(env, key, value);
	if (equal_sign)
		*equal_sign = '=';
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	error;

	if (!args[1])
		return (ft_export_without_args(env));
	error = 0;
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env))
			error = 1;
		i++;
	}
	return (error);
}
