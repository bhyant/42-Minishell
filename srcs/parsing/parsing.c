/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:00:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/17 21:09:27 by tbhuiyan         ###   ########.fr       */
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
	expand_token(shell->token, shell->env, shell->exit_code);
	// Gerer les quotes
	// Remplir la struct command pour l'exec
	return (true);
}
