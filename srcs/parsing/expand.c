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

char	expand_variable(char *str, t_env *env, int exit_code)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				res = write_exit_code();
			// ajout des variables d'env
		}
	}
}

void	expand_token(t_token *token, t_env *env, int exit_code)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == WORD && current->quote_type != SINGLE_QUOTE)
			current = expand_variable(current->str, env, exit_code);
		current = current->next;
	}
}