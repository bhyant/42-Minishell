/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:47:19 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/05/01 10:20:09 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (n <= len_dest)
		return (len_src + n);
	else
	{
		while (src[i] && (len_dest + i < n - 1))
		{
			dest[len_dest + i] = src[i];
			i++;
		}
	}
	if (len_dest < n)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
