/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:23:26 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/04 17:01:34 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_exec_out_dup(t_g *v, char **tab , int i)
{
	int	type;
	int	len;

	(void)v;
	type = 0;
	len = ft_tablen(tab);
	if (tab[i][0] == '>' && tab[i][1] == 0 && i != len - 2)
	{
		type = 1;
		if (!check_outfile(tab[i + 1], 1))
			return (ft_custom_error(NULL, -1, 0));
	}
	else if (tab[i][0] == '>' && tab[i][1] == '>' && i != len - 2)
	{
		type = 0;
		if (!check_outfile(tab[i + 1], 0))
			return (ft_custom_error(NULL, -1, 0));
	}
	return (type);
}

int	ft_exec_out_dup(t_g *v, char **tab, t_l *tmp)
{
	int	i;
	int	len;
	int	type;

	i = -1;
	len = ft_tablen(tab);
	if (!tab)
		return (0);
	while (tab[++i])
	{
		type = cut_exec_out_dup(v, tab, i);
		if (type == -1)
		{
			free(tmp->exec);
			tmp->exec = NULL;
			return (0);
		}
		if (i == len - 1)
		{
			if (tab[i - 1][1] == 0)
				type = 1;
			else
				type = 0;
			if (!check_dup_outfile(tab[i], type, tmp))
			{
				free(tmp->exec);
				tmp->exec = NULL;
				return (0);
			}
		}
	}
	return (1);
}

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
		ft_exec_out_dup(v, tmp->out_tab, tmp);
		return (0);
	}
	return (0);
}
