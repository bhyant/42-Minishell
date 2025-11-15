/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:22:05 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/15 20:03:39 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		env = tmp;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free_redir(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	free_array(char **array, int count)
{
	int	i;
	
	if (!array)
		return ;
	i = 0;
	if (count < 0)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	else
	{
		while (i < count)
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}