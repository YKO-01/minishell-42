/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:18:48 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:19:27 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		count = write (1, "-2147483648", 11);
	else if (n >= 0 && n <= 9)
	{
		count = ft_putchar(n + '0', fd);
	}
	else if (n < 0)
	{
		count = ft_putchar('-', fd);
		count += ft_putnbr(n * -1, fd);
	}
	else
	{
		count = ft_putnbr((n / 10), fd);
		count += ft_putnbr((n % 10), fd);
	}
	return (count);
}
