/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 06:00:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 16:30:00 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_minimal_env(void)
{
	t_env	*env_list;
	char	*pwd;
	char	cwd[4096];

	env_list = NULL;
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		pwd = "/";
	if (!add_to_env_list(&env_list, "PWD", pwd))
		return (free_env(env_list), NULL);
	if (!add_to_env_list(&env_list, "SHLVL", "1"))
		return (free_env(env_list), NULL);
	if (!add_to_env_list(&env_list, "_", "/usr/bin/env"))
		return (free_env(env_list), NULL);
	return (env_list);
}

bool	add_to_env_list(t_env **env_list, char *key, char *value)
{
	t_env	*new_lst;

	new_lst = env_new(key, value);
	if (!new_lst)
		return (false);
	env_add_back(env_list, new_lst);
	return (true);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;

	if (!envp || !envp[0])
		return (create_minimal_env());
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		if (!process_env_entry(&env_list, envp[i]))
			return (free_env(env_list), NULL);
		i++;
	}
	increment_shlvl(&env_list);
	return (env_list);
}
