/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:41:35 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/28 09:48:42 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(char c)
{
	if (c == '|')
		return (true);
	else if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	else
		return (false);
}

t_token	*create_pipe_token(void)
{
	return (token_new(PIPE, NULL));
}

t_token	*create_redir_token(char *entry, size_t *i)
{
	char	redir;
	char	*str;
	t_token	*token;

	redir = entry[*i];
	(*i)++;
	if (entry[*i] == redir)
	{
		str = malloc(3);
		if (!str)
			return (NULL);
		str[0] = redir;
		str[1] = redir;
		str[2] = '\0';
		(*i)++;
	}
	else
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = redir;
		str[1] = '\0';
	}
	(*i)--;
	token = token_new(REDIR, str);
	if (!token)
		free(str);
	return (token);
}

char	*extract_word(char *entry, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*word;

	start = *i;
	while (entry[*i] && !is_operator(entry[*i])
		&& entry[*i] != ' ' && entry[*i] != '\t'
		&& entry[*i] != '"' && entry[*i] != '\'')
		(*i)++;
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, entry + start, len + 1);
	(*i)--;
	return (word);
}

char	*extract_quoted(char *entry, size_t *i, char quote)
{
	size_t	start;
	size_t	len;
	char	*word;

	start = *i;
	(*i)++;
	while (entry[*i] && entry[*i] != quote)
		(*i)++;
	len = *i - start + 1;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, entry + start, len + 1);
	return (word);
}
