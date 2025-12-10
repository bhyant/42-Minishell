/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:22:02 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 14:56:20 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *str, t_type_quote quote_type)
{
	char	*result;
	char	*section;
	int		i;

	(void)quote_type;
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			section = remove_quote_section(str, &i);
		else
			section = extract_unquoted_section(str, &i);
		result = join_section_to_result(result, section);
		if (!result)
			return (NULL);
	}
	return (result);
}

static void	update_token_str(t_token *cur)
{
	char	*new_str;

	new_str = remove_quotes(cur->str, cur->quote_type);
	if (new_str)
	{
		free(cur->str);
		cur->str = new_str;
	}
}

void	process_quotes(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (cur->type == WORD && has_quotes_in_str(cur->str))
			update_token_str(cur);
		cur = cur->next;
	}
}
