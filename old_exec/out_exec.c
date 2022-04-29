/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:15:15 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/13 15:30:45 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_exec_out_dup(t_g *v, char **tab, int i, int len)
{
	int	type;

	type = 0;
	if (tab[i][0] == '>' && tab[i][1] == 0 && i != len - 2)
	{
		type = 1;
		if (!check_outfile(tab[i + 1], 1))
			return (ft_custom_error(NULL, -1, v));
	}
	else if (tab[i][0] == '>' && tab[i][1] == '>' && i != len - 2)
	{
		type = 0;
		if (!check_outfile(tab[i + 1], 0))
			return (ft_custom_error(NULL, -1, v));
	}
	return (type);
}

int	exec_out_dup(t_g *v, char **tab)
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
		type = cut_exec_out_dup(v, tab, i, len);
		if (type == -1)
			return (0);
		if (i == len - 1)
		{
			if (tab[i - 1][1] == 0)
				type = 1;
			else
				type = 0;
			check_dup_outfile(tab[i], type);
		}
	}
	return (1);
}

int	redirect_out(t_g *v)
{
	if (v->l->exec != NULL)
		exec_out_dup(v, v->l->out_tab);
	else
		exec_out(v, v->l->out_tab);
	return (1);
}

int	exec_out(t_g *v, char **tab)
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
				return (ft_custom_error(NULL, 0, v));
		}
		else if (tab[i][0] == '>' && tab[i][1] == '>')
		{
			if (!check_outfile(tab[i + 1], 0))
				return (ft_custom_error(NULL, 0, v));
		}
	}
	return (1);
}
