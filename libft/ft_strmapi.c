/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:57:05 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/05/01 10:25:06 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *str, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*tab;

	i = 0;
	tab = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		tab[i] = f(i, str[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
