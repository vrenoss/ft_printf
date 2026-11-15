/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaganon <rpaganon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 01:58:11 by rpaganon          #+#    #+#             */
/*   Updated: 2026/11/14 01:58:12 by rpaganon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long int	nb;
	int			count;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		count++;
	}
	if (nb >= 10)
		count += ft_putnbr(nb / 10);
	count += ft_putchar('0' + nb % 10);
	return (count);
}

int	ft_putnbr_hex(unsigned int n, char format)
{
	char	*base;
	int		count;

	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		count += ft_putnbr_hex(n / 16, format);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_unsigned(n / 10);
	count += ft_putchar('0' + n % 10);
	return (count);
}

int	ft_putnbr_hex_ul(unsigned long n)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_putnbr_hex_ul(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}
