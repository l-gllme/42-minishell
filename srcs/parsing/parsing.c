/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/25 12:53:22 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_struct(char **tab, t_g *v, char **env, t_list *list)
{
	v->l = malloc(sizeof(t_l));
	v->l->next = NULL;
	v->l->name_in = NULL;
	v->l->name_out = NULL;
	v->tab = tab;
	v->list = list;
	v->env = env;
	v->cmd = NULL;
	v->nb_cmd = 0;
	v->c = 0;
	v->access = 0;
	v->l->in_tab = NULL;
	v->l->out_tab = NULL;
	v->l->exec = NULL;
	v->l->arg = NULL;
	v->fd_in = 0;
	v->file_in = NULL;
	v->urandom = NULL;
	v->retour = 0;
	v->new_env = NULL;
}

static void	cut_dol_replace(t_g *v, int i)
{
	t_l	*t;

	t = NULL;
	t = v->l;
	while (t)
	{
		if (t->arg)
		t->arg = c_env(v, t->arg, 0);
		if (t->exec)
			t->exec = ft_check_in_env_2(v, t->exec, 0, t->arg);
		if (t->in_tab)
		{
			while (t->in_tab[++i])
				if (t->in_tab[i][0] == '<' && t->in_tab[i][1] == 0)
					t->in_tab[i + 1] = c_env(v, t->in_tab[i + 1], 0);
		}
		i = -1;
		if (t->out_tab)
		{
			while (t->out_tab[++i])
				if (t->out_tab[i][0] == '>')
					t->out_tab[i + 1] = c_env(v, t->out_tab[i + 1], 0);
		}
		t = t->next;
	}
}

static void	dol_replace(t_g *v, int i)
{
	if (v->nb_cmd == 1)
	{
		if (v->l->arg)
			v->l->arg = c_env(v, v->l->arg, 0);
		if (v->l->exec)
			v->l->exec = ft_check_in_env_2(v, v->l->exec, 0, v->l->arg);
		if (v->l->in_tab)
		{
			while (v->l->in_tab[++i])
				if (v->l->in_tab[i][0] == '<' && v->l->in_tab[i][1] == 0)
					v->l->in_tab[i + 1] = c_env(v, v->l->in_tab[i + 1], 0);
		}
		i = -1;
		if (v->l->out_tab)
		{
			while (v->l->out_tab[++i])
				if (v->l->out_tab[i][0] == '>')
					v->l->out_tab[i + 1] = c_env(v, v->l->out_tab[i + 1], 0);
		}
	}
	if (v->nb_cmd != 1)
		cut_dol_replace(v, -1);
}

static int	cut_parsing(char *str, t_g *v, char **tab, int c)
{
	if (!get_cmd(str, tab))
		return (ft_custom_error(NULL, 0, v));
	if (!check_not_closed_pipes(tab))
		return (ft_custom_error(NULL, 0, v));
	if (!parse_cmd(v))
		return (0);
	if (c - 2 >= v->nb_cmd)
		return (ft_custom_error("invalid syntax!\n", 0, v));
	return (1);
}

int	parsing(char *str, char **env, t_list *list, int c)
{
	char	**tab;
	t_g		*v;

	if (!ft_check_invalid_signs(str, '<', -1, 0) || !ft_check_invalid_signs(str,
			'>', -1, 0) || !ft_check_weird_signs(str, -1))
		return (0);
	v = malloc(sizeof(t_g));
	if (!v)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	c = count_pipes(str);
	if (c == 0)
	{
		free(v);
		return (0);
	}

	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	init_struct(tab, v, env, list);
	if (!cut_parsing(str, v, tab, c))
		return (0);
	dol_replace(v, -1);
	ft_exec(v, v->l);
	ft_free(v);
	return (1);
}
