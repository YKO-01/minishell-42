/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:07:48 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:16:31 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_lowerhexa(unsigned int n, int fd)
{
	int		count;
	char	*hex;

	hex = "0123456789abcdef";
	count = 0;
	if (n < 16)
		count = ft_putchar(hex[n], fd);
	else
	{
		count = ft_lowerhexa((n / 16), fd);
		count += ft_lowerhexa((n % 16), fd);
	}
	return (count);
}
