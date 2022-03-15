/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:35:00 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/15 15:50:56 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == 0)
		ft_putstr_fd("Malloc error\n", 2);
	if (error == 1)
		ft_putstr_fd("Env/path not found\n", 2);
	if (error == 2)
		ft_putstr_fd("Incorect number of arguments\n\n", 2);
	exit(0);
}
