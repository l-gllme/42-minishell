/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:55:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/31 15:16:54 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_signs(char **tab, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (tab[++i])
	{
		if (tab[i][0] == c)
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	stock_in(t_g *v)
{
	printf("%d\n", count_signs(v->cmd, '<'));
	return (1);
}

int	stock_out(t_g *v)
{
	printf("%d\n", count_signs(v->cmd, '>'));
	return (1);
}

int	stock_exec(t_g *v)
{
	(void)v;
	return (1);
}

int	stock_arg(t_g *v)
{
	(void)v;
	return (1);
}
