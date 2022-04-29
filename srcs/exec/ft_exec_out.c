/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:23:26 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/29 17:24:02 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_out_no_cmd(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '>' && tab[i][1] == 0)
		{
			if (!check_outfile(tab[i + 1], 1))
				return (ft_custom_error(NULL, 0, 0));
		}
		else if (tab[i][0] == '>' && tab[i][1] == '>')
		{
			if (!check_outfile(tab[i + 1], 0))
				return (ft_custom_error(NULL, 0, 0));
		}
	}
	return (1);
}

int	ft_exec_out(t_g *v, t_l *tmp)
{
	(void)v;
	if (!tmp->exec)
	{
		ft_exec_out_no_cmd(tmp->out_tab);
	}
	else
	{
		return (0);
	}
	return (0);
}
