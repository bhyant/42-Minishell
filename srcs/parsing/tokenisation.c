/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:32:20 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/28 09:52:44 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*create_word_token(char *entry, size_t *i, char quote)
{
	char	*str;
	t_token	*token;

	if (quote)
		str = extract_quoted(entry, i, quote);
	else
		str = extract_word(entry, i);
	if (!str)
		return (NULL);
	token = token_new(WORD, str);
	if (!token)
		free(str);
	return (token);
}

t_token	*tokenize(char *entry)
{
	t_token	*tokens;
	t_token	*new_token;
	size_t	i;

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
		else if (entry[i] == '"' || entry[i] == '\'')
			new_token = create_word_token(entry, &i, entry[i]);
		else
			new_token = create_word_token(entry, &i, 0);
		if (!new_token)
			return (ft_tokenclear(&tokens), NULL);
		token_add_back(&tokens, new_token);
	}
	return (tokens);
}

void	add_quote_type(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == WORD)
		{
			if (current->str[0] == '\'')
				current->quote_type = SINGLE_QUOTE;
			else if (current->str[0] == '"')
				current->quote_type = DOUBLE_QUOTE;
			else
				current->quote_type = NO_QUOTE;
		}
		current = current->next;
	}
}
