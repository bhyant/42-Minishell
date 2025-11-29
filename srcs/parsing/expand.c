/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:22:46 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/28 09:50:41 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_single_var(char *str, int *i, t_env *env, int exit_code)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;
	int		start;
	int		var_len;

	start = *i;
	(*i)++;
	var_name = get_var_name(str, i);
	var_value = get_var_value(var_name, env, exit_code);
	if (!var_value)
		var_value = ft_strdup("");
	if (!var_value)
	{
		free(var_name);
		return (NULL);
	}
	var_len = *i - start;
	new_str = replace_in_str(str, var_value, start, var_len);
	*i = start + ft_strlen(var_value);
	free(var_name);
	free(var_value);
	return (new_str);
}

char	*expand_variables(char *str, t_env *env, int exit_code)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	(1 && (i = 0, result = ft_strdup(str)));
	if (!result)
		return (NULL);
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			tmp = expand_single_var(result, &i, env, exit_code);
			if (tmp)
			{
				free(result);
				result = tmp;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (result);
}

void	expand_tokens(t_token *token, t_env *env, int exit_code)
{
	t_token	*current;
	char	*expanded;

	current = token;
	while (current)
	{
		if (current->type == WORD && current->quote_type != SINGLE_QUOTE)
		{
			expanded = expand_variables(current->str, env, exit_code);
			if (expanded)
			{
				free(current->str);
				current->str = expanded;
			}
		}
		current = current->next;
	}
}
