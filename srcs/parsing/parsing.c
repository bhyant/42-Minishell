/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:00:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/14 11:56:08 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parsing(char *entry, t_shell *shell)
{
	if (!parse_entry(entry))
		return (false);
	// faire la tokenisation, le lexer et d'autre cas potentielle a gerer
}
