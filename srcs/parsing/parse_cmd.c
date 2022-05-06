/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:48:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 16:09:42 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_pipe_parse_cmd_2(t_g *v, int choice, t_l *n)
{
	if (!choice)
	{
		v->l->arg = ft_strdup(n->arg);
		v->l->exec = ft_strdup(n->exec);
		v->l->in_tab = ft_tabdup(n->in_tab);
		v->l->out_tab = ft_tabdup(n->out_tab);
		v->l->next = NULL;
	}
	else
	{
		free(n->arg);
		free(n->exec);
		free_char_tab(v->cmd);
		v->cmd = NULL;
		free_char_tab(n->in_tab);
		free_char_tab(n->out_tab);
		n->in_tab = NULL;
		n->out_tab = NULL;
		n->exec = NULL;
		n->arg = NULL;
	}
	return (1);
}

static int	c_p_parse_cmd(t_g *v, t_l *n)
{
	n->in_tab = NULL;
	n->out_tab = NULL;
	n->exec = NULL;
	n->arg = NULL;
	v->l->name_in = NULL;
	v->l->name_out = NULL;
	n->in_tab = stock_in(v, n->in_tab, -1, 0);
	if (g_shell.retour == -999)
		return (ft_custom_error("malloc error in stock_in()\n", 0, v));
	n->out_tab = stock_out(v, n->out_tab, -1, 0);
	if (g_shell.retour == -999)
		return (ft_custom_error("malloc error in stock_in()\n", 0, v));
	n->exec = stock_exec(v, n->exec);
	if (g_shell.retour == -999)
		return (ft_custom_error("error in stock_exec()\n", 0, v));
	n->arg = stock_arg(v, n->arg);
	if (g_shell.retour == -999)
		return (0);
	if (!check_not_followed_sign(v))
		return (ft_custom_error(NULL, 0, NULL));
	return (1);
}

static int	pipe_parse_cmd(t_g *v, t_l *n, int i)
{
	while (v->tab[++i])
	{
		if (!ft_add_spaces(v, '<', i) || !ft_add_spaces(v, '>', i))
			return (ft_custom_error(NULL, 0, v));
		v->cmd = ft_supersplit(v->tab[i], ' ');
		if (!v->cmd)
			return (ft_custom_error("error in ft_supersplit()\n", 0, v));
		if (!c_p_parse_cmd(v, n))
			return (0);
		if (i == 0)
			cut_pipe_parse_cmd_2(v, 0, n);
		else
		{
			ft_super_lstadd_back(&v->l, ft_super_lstnew(ft_tabdup(n->out_tab),
					ft_tabdup(n->in_tab), ft_strdup(n->arg),
					ft_strdup(n->exec)));
		}
		cut_pipe_parse_cmd_2(v, 2, n);
	}	
	return (1);
}

static int	cut_parse_cmd(t_g *v)
{
	if (!ft_add_spaces(v, '<', 0) || !ft_add_spaces(v, '>', 0))
		return (ft_custom_error(NULL, 0, v));
	v->nb_cmd = 1;
	v->cmd = ft_supersplit(v->tab[0], ' ');
	if (!v->cmd)
		return (ft_custom_error("error in ft_supersplit()\n", 0, v));
	v->l->in_tab = stock_in(v, v->l->in_tab, -1, 0);
	if (g_shell.retour == -999)
		return (ft_custom_error("malloc error in stock_in()\n", 0, v));
	v->l->out_tab = stock_out(v, v->l->out_tab, -1, 0);
	if (g_shell.retour == -999)
		return (ft_custom_error("malloc error in stock_out()\n", 0, v));
	if (!check_not_followed_sign(v))
		return (ft_custom_error(NULL, 0, NULL));
	v->l->exec = stock_exec(v, v->l->exec);
	if (g_shell.retour == -999)
		return (ft_custom_error("error in stock_exec()\n", 0, v));
	v->l->arg = stock_arg(v, v->l->arg);
	if (g_shell.retour == -999)
		return (0);
	return (1);
}

int	parse_cmd(t_g *v)
{
	int	i;
	t_l	*n;

	i = ft_tablen(v->tab);
	if (i == 1)
	{
		if (!cut_parse_cmd(v))
			return (0);
	}
	else if (i > 1)
	{
		n = malloc(sizeof(t_l));
		v->nb_cmd = i;
		if (!pipe_parse_cmd(v, n, -1))
		{
			free(n);
			return (0);
		}
		free(n);
	}
	return (1);
}
