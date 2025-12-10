/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:00:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 14:56:20 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quote_section(char *str, int *i)
{
	char	quote;
	int		start;
	char	*section;

	quote = str[*i];
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	section = ft_substr(str, start, *i - start);
	if (str[*i] == quote)
		(*i)++;
	return (section);
}

char	*extract_unquoted_section(char *str, int *i)
{
	int		start;
	char	*section;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	section = ft_substr(str, start, *i - start);
	return (section);
}

char	*join_section_to_result(char *result, char *section)
{
	char	*temp;

	if (!section)
		return (free(result), NULL);
	temp = ft_strjoin(result, section);
	free(result);
	free(section);
	if (!temp)
		return (NULL);
	return (temp);
}

int	has_quotes_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
