/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:55:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/20 13:34:00 by jtaravel         ###   ########.fr       */
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
			if (tab[i + 1])
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
			v->l.in_tab[j] = ft_strdup(v->cmd[i]);
			if (v->cmd[i + 1])
				i++;
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
			v->l.out_tab[j] = ft_strdup(v->cmd[i]);
			if (v->cmd[i + 1])
				i++;
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
		{
			if (v->cmd[i + 1])
				i++;
		}
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
				if (!v->l.arg)
					return (ft_custom_error("malloc error in stock_arg()\n", 0, v));
				v->l.arg = ft_strjoin_gnl(v->l.arg, " ");
				if (!v->l.arg)
					return (ft_custom_error("malloc error in stock_arg()\n", 0, v));
			}
			j = 1;
		}
		else if (v->cmd[i + 1])
			i++;
	}
	//i = ft_strlen(v->l.arg);
	//v->l.arg[i] = 0;
	return (1);
}
