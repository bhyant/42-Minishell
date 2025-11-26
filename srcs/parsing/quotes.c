/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:22:02 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/26 07:25:43 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *str, t_type_quote quote_type)
{
	char	*res;
	int		len;

	if (quote_type == NO_QUOTE)
		return (ft_strdup(str));
	len = ft_strlen(str);
	res = ft_substr(str, 1, len - 2);
	return (res);
}

void	process_quotes(t_token *token)
{
	t_token	*cur;
	char	*new_str;

	cur = token;
	while (cur)
	{
		if (cur->type == WORD && cur->quote_type != NO_QUOTE)
		{
			new_str = remove_quotes(cur->str, cur->quote_type);
			if (new_str)
			{
				free(cur->str);
				cur->str = new_str;
			}
		}
		cur = cur->next;
	}
}
