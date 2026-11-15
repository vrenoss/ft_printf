/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaganon <rpaganon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 19:07:14 by rpaganon          #+#    #+#             */
/*   Updated: 2026/11/14 01:55:37 by rpaganon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>

int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putstr(const char *s);
int		ft_putnbr_hex(unsigned int n, char format);
int		ft_print_unsigned(unsigned int n);
int		ft_putptr(void *ptr);
int		ft_putnbr_hex_ul(unsigned long n);
int		ft_printf(const char *s, ...);
size_t	ft_strlen(const char *s);

#endif
