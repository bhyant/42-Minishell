/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:55:18 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/26 07:27:44 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_type_redir	get_redir_type(char *str)
{
	if (ft_strncmp(str, "<<", 3) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (APPEND);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (IN);
	else
		return (OUT);
}

bool	process_redir(t_token **current, t_command *cmd)
{
	t_type_redir	type;
	t_redir			*new_redir;

	type = get_redir_type((*current)->str);
	*current = (*current)->next;
	if (!*current || (*current)->type != WORD)
		return (false);
	new_redir = create_redir(type, (*current)->str);
	if (!new_redir)
		return (false);
	add_redir_back(&cmd->redir, new_redir);
	return (true);
}

static bool	process_token(t_token **current, t_command *cmd, int *i)
{
	if ((*current)->type == WORD)
	{
		cmd->args[*i] = ft_strdup((*current)->str);
		if (!cmd->args[*i])
			return (false);
		(*i)++;
	}
	else if ((*current)->type == REDIR)
	{
		if (!process_redir(current, cmd))
			return (false);
	}
	return (true);
}

static bool	fill_args(t_token **tokens, t_command *cmd)
{
	int		count;
	int		i;
	t_token	*current;

	count = count_args_until_pipe(*tokens);
	if (count < 0)
		return (false);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return (false);
	i = 0;
	current = *tokens;
	while (current && current->type != PIPE)
	{
		if (!process_token(&current, cmd, &i))
			return (free_array(cmd->args, i), cmd->args = NULL, false);
		current = current->next;
	}
	cmd->args[i] = NULL;
	*tokens = current;
	return (true);
}

t_command	*build_commands(t_token *tokens)
{
	t_command	*cmd_list;
	t_command	*new_cmd;
	t_token		*current;

	cmd_list = NULL;
	current = tokens;
	while (current)
	{
		new_cmd = create_new_command();
		if (!new_cmd)
			return (free_command(cmd_list), NULL);
		if (!fill_args(&current, new_cmd))
			return (free_command(new_cmd), free_command(cmd_list), NULL);
		add_command_back(&cmd_list, new_cmd);
		if (current && current->type == PIPE)
			current = current->next;
	}
	return (cmd_list);
}
