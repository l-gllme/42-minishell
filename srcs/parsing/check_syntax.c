/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:16:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/23 12:30:30 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_cncp(char **tab, int j, int c, int i)
{
	j = -1;
	c = 0;
	while (tab[i][++j])
	{
		if (tab[i][j] == '|' && j == 0)
		{
			j++;
			if (ft_strlen(tab[i]) == 1)
				return (-1);
		}
		if (tab[i][j] != ' ' && tab[i][j] != '\0' && tab[i][j] != '\n')
			c = 1;
	}
	return (c);
}

/* Check for invalid pipes */

int	check_not_closed_pipes(char **tab)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (tab[++i])
	{
		res = cut_cncp(tab, 0, 0, i);
		if (res == 0 || res == -1)
		{
			ft_putstr_fd("Invalid syntax\n", 2);
			return (-1);
		}
	}
	return (1);
}
