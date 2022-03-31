/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:55:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/31 17:53:47 by lguillau         ###   ########.fr       */
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
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = count_signs(v->cmd, '<');
	if (count == 0)
		return (1);
	v->l.in_tab = malloc(sizeof(char *) * (count * 2 + 1));
	if (!v->l.in_tab)
		return (0);
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] == '<')
		{
			v->l.in_tab[j] = v->cmd[i];
			i++;
			j++;
			v->l.in_tab[j] = v->cmd[i];
			j++;
		}
	}
	v->l.in_tab[j] = 0;
	return (1);
}

int	stock_out(t_g *v)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = count_signs(v->cmd, '>');
	if (count == 0)
		return (1);
	v->l.out_tab = malloc(sizeof(char *) * (count * 2 + 1));
	if (!v->l.out_tab)
		return (0);
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] == '>')
		{
			v->l.out_tab[j] = v->cmd[i];
			i++;
			j++;
			v->l.out_tab[j] = v->cmd[i];
			j++;
		}
	}
	v->l.out_tab[j] = 0;
	return (1);
}

int	stock_exec(t_g *v)
{
	int	i;

	i = -1;
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] != '>' && v->cmd[i][0] != '<' && !v->l.exec)
		{
			v->l.exec = ft_strdup(v->cmd[i]);
		}
		else if (v->cmd[i][0] == '>' || v->cmd[i][0] == '<')
			i++;
	}
	return (1);
}

int	stock_arg(t_g *v)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] != '>' && v->cmd[i][0] != '<')
		{
			if (j == 1)
			{
				v->l.arg = ft_strjoin_gnl(v->l.arg, v->cmd[i]);
				v->l.arg = ft_strjoin_gnl(v->l.arg, " ");
				if (!v->l.arg)
					return (0);
			}
			j = 1;
		}
		else
			i++;
	}
	return (1);
}
