/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:19:41 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/07/12 00:33:42 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_printf(int n)
{
	long int	nb;
	int			count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		ft_putchar_printf('-');
		count++;
		nb *= -1;
	}
	if (nb > 9)
		count += ft_putnbr_printf(nb / 10);
	count += ft_putchar_printf((nb % 10) + '0');
	return (count);
}

int	ft_putnbr_unsigned_printf(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_printf(n / 10);
	count += ft_putchar_printf((n % 10) + '0');
	return (count);
}
