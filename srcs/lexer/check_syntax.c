/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:43:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/17 20:44:30 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parse_entry(char *entry)
{
	size_t	i;

	i = 0;
	while (entry[i] == ' ' || entry[i] == '\t')
		i++;
	if (entry[i] == '|' && entry[i + 1] != '|')
		return (printf("bash : syntax error near unexpected token '|'\n"), false);
	while (entry[i])
	{
		if (entry[i] == '"' || entry[i] == '\'')
		{
			if (!check_closed_quote(entry, &i))
				return (false);
		}
		else if (entry[i] == '<' || entry[i] == '>' || entry[i] == '|')
		{
			if (!check_redir_and_pipe(entry, &i))
				return (false);
		}
		i++;
	}
	return (true);
}
