/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:00:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/29 16:14:40 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

char	*join_and_free(char *result, char *part)
{
	char	*temp;

	temp = ft_strjoin(result, part);
	free(result);
	free(part);
	return (temp);
}

char	*handle_quoted_part(char *entry, size_t *i, char *result)
{
	char	*part;
	char	*temp;

	part = extract_quoted(entry, i, entry[*i]);
	if (!part)
		return (free(result), NULL);
	temp = join_and_free(result, part);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*handle_unquoted_part(char *entry, size_t *i, char *result)
{
	size_t	start;
	char	*part;
	char	*temp;

	start = *i;
	while (entry[*i] && !is_delimiter(entry[*i])
		&& entry[*i] != '"' && entry[*i] != '\'')
		(*i)++;
	part = ft_substr(entry, start, *i - start);
	if (!part)
		return (free(result), NULL);
	temp = join_and_free(result, part);
	return (temp);
}

char	*build_composite_word(char *entry, size_t *i)
{
	char	*result;

	result = ft_strdup("");
	while (entry[*i] && !is_delimiter(entry[*i]))
	{
		if (entry[*i] == '"' || entry[*i] == '\'')
		{
			result = handle_quoted_part(entry, i, result);
			if (!result)
				return (NULL);
			if (entry[*i] && is_delimiter(entry[*i]))
				break ;
		}
		else
		{
			result = handle_unquoted_part(entry, i, result);
			if (!result)
				return (NULL);
		}
	}
	(*i)--;
	return (result);
}
