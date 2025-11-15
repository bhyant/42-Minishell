/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:32:20 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/14 20:13:43 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokenize(char *entry)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (entry[i])
	{
		while (entry[i] == ' ' || entry[i] == '\t')
			i++;
		if (!entry[i])
			break ;
		if (entry[i] == '|')
			token_add_back(&tokens, create_pipe_token());
		else if (entry[i] == '<' || entry[i] == '>')
			token_add_back(&tokens, create_redir_token(entry, &i));
		else if (entry[i] == '"' || entry[i] == '\'')
			token_add_back(&tokens, token_new(WORD,
					extract_quoted(entry, &i, entry[i])));
		else
			token_add_back(&tokens, token_new(WORD, extract_word(entry, &i)));
		i++;
	}
	return (tokens);
}
