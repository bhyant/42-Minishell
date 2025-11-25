/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:15:12 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/25 19:57:14 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_node(t_env *env)
{
	int		count;
	t_env	*node;

	node = env;
	count = 0;
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}

static char	*create_env_array(t_env *env)
{
	char	*array_key;
	char	*env_array;

	array_key = ft_strjoin(env->key, "=");
	if (!array_key)
		return (NULL);
	env_array = ft_strjoin(array_key, env->value);
	if (!env_array)
		return (free(array_key), NULL);
	free(array_key);
	return (env_array);
}

char	**create_env(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		count;
	int		i;

	count = count_env_node(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = create_env_array(tmp);
		if (!envp[i])
			return (free_array(envp, i), NULL);
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
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
	char	*equal;
	char	*key;
	char	*value;
	int		i;

	(1 && (env_list = NULL, i = -1));
	while (envp[++i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue ;
		}
		key = ft_substr(envp[i], 0, equal - envp[i]);
		value = ft_strdup(equal + 1);
		if (!value || !key)
			return (free(key), free_env(env_list), NULL);
		if (!add_to_env_list(&env_list, key, value))
			return (free(value), free(key), free_env(env_list), NULL);
		free(key);
		free(value);
	}
	return (env_list);
}
