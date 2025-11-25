/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:04:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/25 17:32:15 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_closed_quote(char *entry, size_t *i)
{
	char	quote;

	quote = entry[*i];
	(*i)++;
	while (entry[*i] && entry[*i] != quote)
		(*i)++;
	if (!entry[*i])
		return (printf("syntax error : quote must be closed\n"), false);
	return (true);
}

bool	check_after_pipe(char *entry, size_t *i)
{
	while (entry[*i] == ' ' || entry[*i] == '\t')
		(*i)++;
	if (!entry[*i])
		return (false);
	if (entry[*i] == '|')
		return (false);
	return (true);
}

bool	check_redir(char *entry, size_t *i)
{
	char	redir;

	redir = entry[*i];
	(*i)++;
	if (entry[*i] == redir)
		(*i)++;
	while (entry[*i] == ' ' || entry[*i] == '\t')
		(*i)++;
	if (!entry[*i])
		return (printf("bash: syntax error near unexpected token `newline'\n")
			, false);
	else if (entry[*i] == '|')
		return (printf("bash: syntax error near unexpected token `%c'\n",
				entry[*i]), false);
	else if (entry[*i] == '<' || entry[*i] == '>')
		return (printf("bash: syntax error near unexpected token `%c'\n",
				entry[*i]), false);
	return (true);
}

bool	check_redir_and_pipe(char *entry, size_t *i)
{
	char	operator;

	operator = entry[*i];
	if (operator == '|')
	{
		(*i)++;
		if (entry[*i] == '|')
		{
			(*i)++;
			if (!check_after_pipe(entry, i))
				return (printf("bash: syntax error near unexpected token `||'\n")
					, false);
		}
		else if (!check_after_pipe(entry, i))
		{
			return (printf("bash: syntax error near unexpected token `|'\n")
				, false);
		}
	}
	else
	{
		if (!check_redir(entry, i))
			return (false);
	}
	return (true);
}
