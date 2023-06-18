/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osajide <osajide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:59:04 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/06/15 15:34:02 by osajide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	char pwd[PATH_MAX];
	char *path;

	if (getcwd(pwd, sizeof(pwd)))
		ft_printf(1, "%s\n", pwd);
	general.exit_status = 0;
}