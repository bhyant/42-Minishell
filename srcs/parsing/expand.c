/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:22:46 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/17 22:00:06 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_variable(char *str, t_env *env, int exit_code)
{
	char	*result;
	int		new_len;

	if (!str)
		return (NULL);
	new_len = expand_len(str, env, exit_code);
	result = malloc(sizeof(char) * (new_len + 1));
	if (!result)
		return (NULL);
	copy_expand(result, str, env, exit_code);
	return (result);
}

void	expand_token(t_token *token, t_env *env, int exit_code)
{
	t_token	*current;
	char	*expand_value;

	current = token;
	while (current)
	{
		if (current->type == WORD && current->quote_type != SINGLE_QUOTE)
		{
			if (ft_strchr(current->str, '$'))
			{
				expand_value = expand_variable(current->str, env, exit_code);
				if (expand_value)
				{
					free(current->str);
					current->str = expand_value;
				}
			}
		}
		current = current->next;
	}
}

