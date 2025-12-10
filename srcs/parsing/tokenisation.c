/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:32:20 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 14:56:20 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_quote_type(t_token *token)
{
	t_token	*current;
	int		i;
	int		has_quote;

	current = token;
	while (current)
	{
		if (current->type == WORD)
		{
			i = 0;
			has_quote = 0;
			while (current->str[i])
			{
				if (current->str[i] == '\'' || current->str[i] == '"')
				{
					has_quote = 1;
					break ;
				}
				i++;
			}
			current->quote_type = quote_type_chooser(current, has_quote);
		}
		current = current->next;
	}
}

t_type_quote	quote_type_chooser(t_token *current, int has_quote)
{
	if (!has_quote)
		return (NO_QUOTE);
	else if (current->str[0] == '\'')
		return (SINGLE_QUOTE);
	else if (current->str[0] == '"')
		return (DOUBLE_QUOTE);
	else
		return (NO_QUOTE);
}
