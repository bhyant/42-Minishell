/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:00:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/16 22:42:59 by tbhuiyan         ###   ########.fr       */
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
	// Gerer l'expand
	// Gerer les quotes
	// Remplir la struct command pour l'exec
	return (true);
}
