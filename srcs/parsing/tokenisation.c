/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:32:20 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/07 17:03:17 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_composite_word(char *entry, size_t *i)
{
	char	*result;
	char	*temp;
	char	*part;
	size_t	start;

	result = ft_strdup("");
	start = *i;
	while (entry[*i] && entry[*i] != ' ' && entry[*i] != '\t'
		&& entry[*i] != '|' && entry[*i] != '<' && entry[*i] != '>')
	{
		if (entry[*i] == '"' || entry[*i] == '\'')
		{
			part = extract_quoted(entry, i, entry[*i]);
			if (!part)
				return (free(result), NULL);
			temp = ft_strjoin(result, part);
			free(result);
			free(part);
			if (!temp)
				return (NULL);
			result = temp;
			if (entry[*i] && (entry[*i] == ' ' || entry[*i] == '\t'
				|| entry[*i] == '|' || entry[*i] == '<' || entry[*i] == '>'))
				break ;
		}
		else
		{
			start = *i;
			while (entry[*i] && entry[*i] != ' ' && entry[*i] != '\t'
				&& entry[*i] != '|' && entry[*i] != '<' && entry[*i] != '>'
				&& entry[*i] != '"' && entry[*i] != '\'')
				(*i)++;
			part = ft_substr(entry, start, *i - start);
			if (!part)
				return (free(result), NULL);
			temp = ft_strjoin(result, part);
			free(result);
			free(part);
			if (!temp)
				return (NULL);
			result = temp;
		}
	}
	(*i)--;
	return (result);
}

t_token	*tokenize(char *entry)
{
	t_token	*tokens;
	t_token	*new_token;
	size_t	i;
	char	*word;

	tokens = NULL;
	i = -1;
	while (entry[++i])
	{
		while (entry[i] == ' ' || entry[i] == '\t')
			i++;
		if (!entry[i])
			break ;
		if (entry[i] == '|')
			new_token = create_pipe_token();
		else if (entry[i] == '<' || entry[i] == '>')
			new_token = create_redir_token(entry, &i);
		else
		{
			word = build_composite_word(entry, &i);
			if (!word)
				return (ft_tokenclear(&tokens), NULL);
			new_token = token_new(WORD, word);
			if (!new_token)
				free(word);
		}
		if (!new_token)
			return (ft_tokenclear(&tokens), NULL);
		token_add_back(&tokens, new_token);
	}
	return (tokens);
}

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
