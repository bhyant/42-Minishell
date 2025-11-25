/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:21:30 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/25 22:21:16 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parsing(char *entry, t_shell *shell)
{
	if (!parse_entry(entry))
		return (false);
	shell->token = tokenize(entry);
	if (!shell->token)
		return (false);
	add_quote_type(shell->token);
	expand_tokens(shell->token, shell->env, shell->exit_code);
	process_quotes(shell->token);
	// Remplir la struct command pour l'exec
	return (true);
}
