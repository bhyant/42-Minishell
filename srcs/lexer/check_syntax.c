/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:43:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/03 05:20:00 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_initial_syntax(char *entry, size_t *i)
{
	while (entry[*i] == ' ' || entry[*i] == '\t')
		(*i)++;
	if (entry[*i] == '|')
		return (printf("bash : syntax error near unexpected token '|'\n")
			, false);
	if (entry[*i] == '&')
		return (printf("bash : syntax error near unexpected token '&'\n")
			, false);
	return (true);
}

bool	parse_entry(char *entry)
{
	size_t	i;

	i = 0;
	if (!check_initial_syntax(entry, &i))
		return (false);
	while (entry[i])
	{
		if (entry[i] == '"' || entry[i] == '\'')
		{
			if (!check_closed_quote(entry, &i))
				return (false);
		}
		else if (entry[i] == '<' || entry[i] == '>' || entry[i] == '|'
			|| entry[i] == '&')
		{
			if (!check_redir_and_pipe(entry, &i))
				return (false);
		}
		i++;
	}
	return (true);
}
