/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:21:30 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/05 08:37:09 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parsing(char *entry, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (entry[i] && (entry[i] == ' ' || entry[i] == '\t'))
		i++;
	if (!entry[i])
		return (true);
	if (!parse_entry(entry))
		return (false);
	shell->token = tokenize(entry);
	if (!shell->token)
		return (true);
	add_quote_type(shell->token);
	expand_tokens(shell->token, shell->env, shell->exit_code);
	process_quotes(shell->token);
	shell->command = build_commands(shell->token);
	if (!shell->command)
		return (ft_tokenclear(&shell->token), shell->token = NULL, false);
	return (true);
}
