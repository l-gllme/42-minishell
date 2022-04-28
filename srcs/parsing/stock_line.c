/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:55:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/28 17:06:35 by lguillau         ###   ########.fr       */
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

char	**stock_in(t_g *v, char **in_tab)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = count_signs(v->cmd, '<');
	if (count == 0)
		return (in_tab);
	in_tab = malloc(sizeof(char *) * (count * 2 + 1));
	if (!in_tab)
	{
		g_retour = -999;
		return (0);
	}
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] == '<')
		{
			in_tab[j] = ft_strdup(v->cmd[i]);
			if (v->cmd[i + 1])
				i++;
			j++;
			in_tab[j] = ft_strdup(v->cmd[i]);
			j++;
		}
	}
	in_tab[j] = 0;
	return (in_tab);
}

char	**stock_out(t_g *v, char **out_tab)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = count_signs(v->cmd, '>');
	if (count == 0)
		return (out_tab);
	out_tab = malloc(sizeof(char *) * (count * 2 + 1));
	if (!out_tab)
	{
		g_retour = -999;
		return (0);
	}
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] == '>')
		{
			out_tab[j] = ft_strdup(v->cmd[i]);
			if (v->cmd[i + 1])
				i++;
			j++;
			out_tab[j] = ft_strdup(v->cmd[i]);
			j++;
		}
	}
	out_tab[j] = 0;
	return (out_tab);
}

char	*stock_exec(t_g *v, char *exec)
{
	int	i;
	int	l;

	i = -1;
	l = -1;
	while (v->cmd[++i])
	{
		if (v->cmd[i][0] != '>' && v->cmd[i][0] != '<' && !exec)
		{
			while (v->cmd[i][++l] == ' ')
				;
			exec = ft_strdup(v->cmd[i] + l);
			if (!exec)
			{
				g_retour = -999;
				return (ft_char_error("malloc error in stock_exec)\n", 0, v));
			}
		}
		else if (v->cmd[i][0] == '>' || v->cmd[i][0] == '<')
		{
			if (v->cmd[i + 1])
				i++;
		}
	}
	return (exec);
}

char	*stock_arg(t_g *v, char *arg)
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
				arg = ft_strjoin_gnl(arg, v->cmd[i]);
				if (!arg)
				{
					g_retour = -999;
					return (ft_char_error("malloc error in stock_arg()\n", 0, v));
				}
				arg = ft_strjoin_gnl(arg, " ");
				if (!arg)
				{
					g_retour = -999;
					return (ft_char_error("malloc error in stock_arg()\n", 0, v));
				}
			}
			j = 1;
		}
		else if (v->cmd[i + 1])
			i++;
	}
	if (arg)
		arg[ft_strlen(arg) - 1] = 0;
	return (arg);
}
