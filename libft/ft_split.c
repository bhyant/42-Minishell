/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:01:11 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/05/12 12:28:18 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i + 1] == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

static int	ft_lenword(const char *s, char set, int i)
{
	int	count;

	count = 0;
	while (s[i] == set)
		i++;
	while (s[i] != set && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static void	ft_freem(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	ft_fill(char **result, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		result[j] = malloc((ft_lenword(s, c, i) + 1) * sizeof(char));
		if (!result[j])
		{
			ft_freem(result);
			return (-1);
		}
		while (s[i] && s[i] != c)
			result[j][k++] = s[i++];
		result[j][k] = '\0';
		j++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (ft_fill(result, s, c) == -1)
		return (NULL);
	result[ft_countword(s, c)] = NULL;
	return (result);
}
