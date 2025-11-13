/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:04:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/13 13:30:09 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_closed_quote(char *str, size_t *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
		return (printf("Error : quote must be closed"));
	return (true);
}

bool	check_redir_and_pipe(char *str, size_t *i)
{
	char	redir;

	redir = str[*i];
	(*i)++;
	while (str[*i] &&)
		(*i)++;
	// a finir
}