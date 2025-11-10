/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:10:35 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/05/01 10:19:36 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (start >= ft_strlen(str))
	{
		tab = malloc(1);
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = str[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
