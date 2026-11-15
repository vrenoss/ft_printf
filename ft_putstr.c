/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaganon <rpaganon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:28:36 by rpaganon          #+#    #+#             */
/*   Updated: 2026/11/14 01:54:55 by rpaganon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stddef.h>

int	ft_putstr(const char *s)
{
	size_t	size;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	size = ft_strlen(s);
	write(1, s, size);
	return (size);
}
