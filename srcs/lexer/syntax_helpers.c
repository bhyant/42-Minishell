/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 05:35:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/03 05:26:40 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_pipe_operator(char *entry, size_t i)
{
	if (entry[i] == '|')
	{
		if (entry[i + 1] == '|')
			return (printf("bash: syntax error near unexpected token `||'\n")
				, false);
		return (printf("bash: syntax error near unexpected token `|'\n")
			, false);
	}
	return (true);
}

bool	check_redir_operator(char *entry, size_t i)
{
	if (entry[i] == '<' || entry[i] == '>')
	{
		if (entry[i] == entry[i + 1])
			return (printf("bash: syntax error near unexpected token `%c%c'\n",
					entry[i], entry[i]), false);
		return (printf("bash: syntax error near unexpected token `%c'\n",
				entry[i]), false);
	}
	return (true);
}

bool	check_pipe_token(char *entry, size_t *i)
{
	(*i)++;
	if (entry[*i] == '|')
		return (printf("bash: syntax error near unexpected token `||'\n")
			, false);
	return (check_after_pipe(entry, i));
}

bool	check_and_token(char *entry, size_t *i)
{
	(*i)++;
	if (entry[*i] == '&')
		return (printf("bash: syntax error near unexpected token `&&'\n")
			, false);
	return (printf("bash: syntax error near unexpected token `&'\n")
		, false);
}
