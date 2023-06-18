/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:28:24 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:16:53 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_pointer(unsigned long n, int fd)
{
	int		count;
	char	*hex;

	hex = "0123456789abcdef";
	count = 0;
	if (n < 16)
		count = ft_putchar(hex[n], fd);
	else
	{
		count = ft_pointer((n / 16), fd);
		count += ft_pointer((n % 16), fd);
	}
	return (count);
}
