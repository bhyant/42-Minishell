/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:29:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/05/01 10:57:47 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnumber(int n)
{
	size_t	count;
	long	nbr;

	count = 0;
	nbr = n;
	if (nbr <= 0)
		count = 1;
	while (nbr)
	{
		nbr /= 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*tab;
	long	nb;
	int		len;

	nb = n;
	len = ft_countnumber(n);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	len--;
	if (nb == 0)
		tab[0] = '0';
	if (nb < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		tab[len] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (tab);
}
