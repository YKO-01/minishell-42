/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:14:46 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:19:01 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static	int	p_check(va_list args, const char *s, int fd)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s[i] == 'c')
		count = ft_putchar(va_arg(args, int), fd);
	else if (s[i] == 's')
		count = ft_putstr(va_arg(args, char *), fd);
	else if (s[i] == 'd' || s[i] == 'i')
		count = ft_putnbr(va_arg(args, int), fd);
	else if (s[i] == 'u')
		count = ft_unputnbr(va_arg(args, unsigned int), fd);
	else if (s[i] == 'X')
		count = ft_upperhexa(va_arg(args, unsigned int), fd);
	else if (s[i] == 'x')
		count = ft_lowerhexa(va_arg(args, unsigned int), fd);
	else if (s[i] == 'p')
	{
		count = ft_putstr("0x", fd);
		count += ft_pointer(va_arg(args, unsigned long), fd);
	}
	else if (s[i] == '%')
		count = ft_putchar('%', fd);
	return (count);
}

int	ft_printf(int fd, const char *s, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			count += p_check(args, &s[i], fd);
		}
		else
			count += ft_putchar(s[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
