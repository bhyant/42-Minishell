/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/25 11:40:58 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str + start, len + 1);
	return (name);
}

char	*get_var_value(char *name, t_env *env, int exit_code)
{
	char	*value;

	if (!name)
		return (ft_strdup("$"));
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(exit_code));
	value = env_get_value(env, name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	calculate_new_len(char *str, char *value, int var_len)
{
	int	new_len;

	new_len = ft_strlen(str) - var_len + ft_strlen(value);
	return (new_len);
}

char	*replace_in_str(char *str, char *value, int start, int var_len)
{
	char	*new_str;
	int		new_len;
	int		i;
	int		j;

	new_len = calculate_new_len(str, value, var_len);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < start)
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (value[j])
		new_str[i++] = value[j++];
	j = start + var_len;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	return (new_str);
}
