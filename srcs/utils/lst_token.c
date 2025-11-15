/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:22:35 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/15 21:03:55 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

t_token	*token_new(t_type_token type, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*token_last(t_token *tokens)
{
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

void	token_add_back(t_token **lst, t_token *new)
{
	if (!lst)
		return ;
	if (*lst)
		token_last(*lst)->next = new;
	else
		*lst = new;
}

void	ft_tokenclear(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->str)
			free((*tokens)->str);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}
