/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:00:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/15 20:10:50 by tbhuiyan         ###   ########.fr       */
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
	// A faire expand et gerer les quote
	return (true);
}
