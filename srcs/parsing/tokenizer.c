/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:33:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 14:41:26 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces(char *entry, size_t *i)
{
	while (entry[*i] == ' ' || entry[*i] == '\t')
		(*i)++;
}

static t_token	*create_word_token(char *entry, size_t *i)
{
	t_token	*new_token;
	char	*word;

	word = build_composite_word(entry, i);
	if (!word)
		return (NULL);
	new_token = token_new(WORD, word);
	if (!new_token)
		free(word);
	return (new_token);
}

static t_token	*process_next_token(char *entry, size_t *i)
{
	if (entry[*i] == '|')
		return (create_pipe_token());
	else if (entry[*i] == '<' || entry[*i] == '>')
		return (create_redir_token(entry, i));
	else
		return (create_word_token(entry, i));
}

t_token	*tokenize(char *entry)
{
	t_token	*tokens;
	t_token	*new_token;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (entry[i])
	{
		skip_spaces(entry, &i);
		if (!entry[i])
			break ;
		new_token = process_next_token(entry, &i);
		if (!new_token)
			return (ft_tokenclear(&tokens), NULL);
		token_add_back(&tokens, new_token);
		i++;
	}
	return (tokens);
}
