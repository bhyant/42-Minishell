/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:26:36 by asmati            #+#    #+#             */
/*   Updated: 2025/11/13 10:26:36 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key); // *Je copie la clé" HOME'
	new->value = ft_strdup(value); // Je copie la valeur : 'home/user'
	new->next = NULL;  // Null next pointer
	return (new); // return le new noeud
}
// trouve le chemin
t_env	*env_find(t_env *env,char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0) // Si trouver return env sinon null
			return (env);
		env = env->next;
	}
	return (NULL);
}
// ma valeur clef exemple LS ou Cat pas le chemin
char	*env_get_value(t_env *env, char *key)
{
	t_env	*node;

	node = env_find(env, key);
	if (node)
		return (node->value);
	return (NULL);
}

void	env_set(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = env_find (env, key);
	if (node)
	{
		free (node->value);
		node->value = ft_strdup (value);
	}
	else
	{
		node = env_new (key, value);
		env_add_back (env, node);
	}
}

void	env_remove(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free (current->key);
			free (current->value);
			free (current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new) //si noeud null
		return ;
	if (!*env) //si list vide
	{
		*env = new;
		return ;
	}
	last = *env; //sinon run jusqu'au last noeud
	while (last->next)
		last = last->next;
	last->next = new;
}
