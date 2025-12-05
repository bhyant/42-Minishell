/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:22:02 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/05 08:37:09 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_quote_section(char *str, int *i)
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

char	*remove_quotes(char *str, t_type_quote quote_type)
{
	char	*result;
	char	*temp;
	char	*section;
	int		i;
	int		start;

	(void)quote_type;
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			section = remove_quote_section(str, &i);
		else
		{
			start = i;
			while (str[i] && str[i] != '"' && str[i] != '\'')
				i++;
			section = ft_substr(str, start, i - start);
		}
		if (!section)
			return (free(result), NULL);
		temp = ft_strjoin(result, section);
		free(result);
		free(section);
		if (!temp)
			return (NULL);
		result = temp;
	}
	return (result);
}

void	process_quotes(t_token *token)
{
	t_token	*cur;
	char	*new_str;
	int		i;
	int		has_quote;

	cur = token;
	while (cur)
	{
		if (cur->type == WORD)
		{
			i = 0;
			has_quote = 0;
			while (cur->str[i])
			{
				if (cur->str[i] == '"' || cur->str[i] == '\'')
					has_quote = 1;
				i++;
			}
			if (has_quote)
			{
				new_str = remove_quotes(cur->str, cur->quote_type);
				if (new_str)
				{
					free(cur->str);
					cur->str = new_str;
				}
			}
		}
		cur = cur->next;
	}
}
