/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:30:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:53:53 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_shlvl_value(char *shlvl_str)
{
	int	value;
	int	i;

	if (!shlvl_str)
		return (1);
	i = 0;
	while (shlvl_str[i] == ' ' || shlvl_str[i] == '\t')
		i++;
	if (shlvl_str[i] == '-' || !ft_isdigit(shlvl_str[i]))
		return (1);
	value = ft_atoi(shlvl_str);
	if (value < 0)
		return (1);
	return (value + 1);
}

void	increment_shlvl(t_env **env_list)
{
	char	*current_shlvl;
	int		new_value;
	char	*new_shlvl_str;

	current_shlvl = env_get_value(*env_list, "SHLVL");
	new_value = get_shlvl_value(current_shlvl);
	new_shlvl_str = ft_itoa(new_value);
	if (!new_shlvl_str)
		return ;
	env_set(env_list, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
}

bool	process_env_entry(t_env **env_list, char *entry)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return (true);
	key = ft_substr(entry, 0, equal - entry);
	value = ft_strdup(equal + 1);
	if (!value || !key)
		return (free(key), false);
	if (!add_to_env_list(env_list, key, value))
		return (free(value), free(key), false);
	free(key);
	free(value);
	return (true);
}
