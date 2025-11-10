/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:01:41 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/04/29 13:20:06 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*dest;

	start = 0;
	end = ft_strlen(str);
	i = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
