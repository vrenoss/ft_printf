/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaganon <rpaganon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 01:21:47 by rpaganon          #+#    #+#             */
/*   Updated: 2026/11/17 16:11:15 by rpaganon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	ft_printf_arg(char type, va_list *ap)
{
	int	count;

	count = 0;
	if (type == 'd' || type == 'i')
		count = ft_putnbr(va_arg(*ap, int));
	else if (type == 'p')
		count = ft_putptr(va_arg(*ap, void *));
	else if (type == 'u')
		count = ft_print_unsigned(va_arg(*ap, unsigned int));
	else if (type == 'c')
		count = ft_putchar((char)va_arg(*ap, int));
	else if (type == 's')
		count = ft_putstr(va_arg(*ap, char *));
	else if (type == '%')
		count = ft_putchar('%');
	else if (type == 'x' || type == 'X')
		count = ft_putnbr_hex(va_arg(*ap, unsigned int), type);
	return (count);
}

static int	is_arg(char c)
{
	char	*args;
	int		i;

	i = 0;
	args = "cspdiuxX%";
	while (args[i])
	{
		if (args[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	ap;

	if (!s)
		return (-1);
	va_start(ap, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%' && is_arg(s[i + 1]))
		{
			count += ft_printf_arg(s[i + 1], &ap);
			i++;
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
/*
#include <stdio.h>
int	main(void)
{
	int	x;
	
	x = 18;
	ft_printf("%s\n", "voiture");
	printf("%s\n", "voiture");
	return (0);
}
*/
