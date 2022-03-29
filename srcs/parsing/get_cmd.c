/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:07:03 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/29 14:30:44 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_gc_struct(t_c *c)
{
	c->i = -1;
	c->j = 0;
	c->k = 0;
	c->l = 0;
	c->sq_opened = 0;
	c->dq_opened = 0;
}

static void	cut_gc(char str, t_c *c)
{
	if (str == '\'' && c->dq_opened == 0)
	{
		if (c->sq_opened)
			c->sq_opened = 0;
		else
			c->sq_opened = 1;
	}
	if (str == '"' && c->sq_opened == 0)
	{
		if (c->dq_opened)
			c->dq_opened = 0;
		else
			c->dq_opened = 1;
	}
}

static int	cut_gc_2(t_c *c, char *str, char **tab)
{
	if (((str[c->i] == '&' && str[c->i + 1] == '&') || (str[c->i]
				== '|' && str[c->i - 1] != '|') || (str[c->i] == '|'
				&& str[c->i + 1] == '|')) && !c->dq_opened && !c->sq_opened)
	{
		tab[c->k] = malloc(sizeof(char *) * (c->i + 1 - c->j));
		if (!tab[c->k])
		{
			ft_putstr_fd("Malloc Error in get_cmd()\n", 2);
			return (0);
		}
		c->l = 0;
		while (c->j < c->i)
		{
			tab[c->k][c->l] = str[c->j];
			c->j++;
			c->l++;
		}
		tab[c->k][c->j] = 0;
		c->k++;
		c->j = c->i;
	}
	return (1);
}

static int	cut_gc_3(t_c *c, char *str, char **tab)
{
	tab[c->k] = malloc(sizeof(char *) * (ft_strlen(str + c->j) + 1));
	if (!tab[c->k])
	{
		ft_putstr_fd("Malloc Error in get_cmd()\n", 2);
		return (0);
	}
	c->i = 0;
	while (str[c->j])
	{
		tab[c->k][c->i] = str[c->j];
		c->i++;
		c->j++;
	}
	tab[c->k][c->i] = 0;
	c->k++;
	tab[c->k] = 0;
	return (1);
}

int	get_cmd(char *str, char **tab)
{
	t_c	*c;

	c = malloc(sizeof(t_c));
	if (!c)
	{
		ft_putstr_fd("Malloc Error in get_cmd()\n", 2);
		return (0);
	}
	init_gc_struct(c);
	c->k = 0;
	while (str[++c->i])
	{
		cut_gc(str[c->i], c);
		if (!cut_gc_2(c, str, tab))
			return (0);
	}
	if (!cut_gc_3(c, str, tab))
		return (0);
	free(c);
	return (1);
}
