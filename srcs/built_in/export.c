/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/21 09:48:04 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_identifier(char *str) // 
{
	int	i;
	
	if(!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while(str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_export(char **args, t_env **env) //
{
	int		i;
	int		error;
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*current;

	if(!args[1])
	{
		current = *env;
		while(current)
		{
			printf("declare -x %s=\"%s\"\n", current->key,current->value);
			current = current->next;
		}
		return 0;
	}
	error = 0;
	i = 1;
	while(args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		
		if(equal_sign)
		{
			*equal_sign = '\0';
			key = args[i];
			value = equal_sign + 1;
		}
		else
		{
			key = args[i];
			value = "";
		}
		
		if(!is_valid_identifier(key))
		{
			 ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
			error = 1;
			if(equal_sign)
				*equal_sign = '=';
			i++;
			continue;
		}
		env_set(env, key, value);
		if(equal_sign)
			*equal_sign = '=';
		i++;
	}
	return (error);
}
