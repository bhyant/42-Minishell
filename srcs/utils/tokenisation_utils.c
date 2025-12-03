/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:41:35 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/03 05:18:10 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_pipe_token(void)
{
	return (token_new(PIPE, NULL));
}

static char	*create_double_redir(char redir)
{
	char	*str;

	str = malloc(3);
	if (!str)
		return (NULL);
	str[0] = redir;
	str[1] = redir;
	str[2] = '\0';
	return (str);
}

static char	*create_single_redir(char redir)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = redir;
	str[1] = '\0';
	return (str);
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
		str = create_double_redir(redir);
		(*i)++;
	}
	else
		str = create_single_redir(redir);
	if (!str)
		return (NULL);
	(*i)--;
	token = token_new(REDIR, str);
	if (!token)
		free(str);
	return (token);
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
