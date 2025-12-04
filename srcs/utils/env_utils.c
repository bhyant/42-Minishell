/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:15:12 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/04 21:30:29 by asmati           ###   ########.fr       */
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

	if (!env->value)
		return (ft_strdup(env->key));
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
