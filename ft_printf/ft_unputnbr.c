/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:00:53 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:19:56 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_unputnbr(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
	{
		count = ft_putchar(n + '0', fd);
	}
	else
	{
		count = ft_putnbr((n / 10), fd);
		count += ft_putnbr((n % 10), fd);
	}
	return (count);
}
