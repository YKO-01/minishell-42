/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:20:30 by osajide           #+#    #+#             */
/*   Updated: 2023/06/12 16:18:42 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<unistd.h>
# include<stdarg.h>

int	ft_putchar(char c, int fd);
int	ft_putstr(char *s, int fd);
int	ft_putnbr(int n, int fd);
int	ft_unputnbr(unsigned int n, int fd);
int	ft_upperhexa(unsigned int n, int fd);
int	ft_lowerhexa(unsigned int n, int fd);
int	ft_pointer(unsigned long n, int fd);
int	ft_printf(int fd, const char *s, ...);
#endif
