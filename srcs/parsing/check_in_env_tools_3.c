/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_tools_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:42:17 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/25 12:42:33 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			g_shell.check++;
		i++;
	}
}
