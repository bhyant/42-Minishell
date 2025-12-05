/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 06:01:25 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/04 21:14:13 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->pid = -1;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_command_back(t_command **list, t_command *new)
{
	t_command	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	count_args_until_pipe(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
			count++;
		else if (current->type == REDIR)
		{
			current = current->next;
			if (!current || current->type != WORD)
				return (-1);
		}
		current = current->next;
	}
	return (count);
}

t_redir	*create_redir(t_type_redir type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	redir->type = type;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir_back(t_redir **list, t_redir *new)
{
	t_redir	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}
