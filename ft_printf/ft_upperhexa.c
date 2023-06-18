/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upperhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:17:37 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:20:12 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_upperhexa(unsigned int n, int fd)
{
	int		count;
	char	*hex;

	hex = "0123456789ABCDEF";
	count = 0;
	if (n < 16)
		count = ft_putchar(hex[n], fd);
	else
	{
		count = ft_upperhexa((n / 16), fd);
		count += ft_upperhexa((n % 16), fd);
	}
	return (count);
}
