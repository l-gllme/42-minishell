/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/10 11:33:31 by jtaravel         ###   ########.fr       */
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

static void	dol_replace(t_g *v)
{
	t_l		*tmp;

	tmp = NULL;
	if (v->nb_cmd == 1)
	{
		if (v->l->arg)
			v->l->arg = ft_check_in_env(v, v->l->arg, 0);
		if (v->l->exec)
			v->l->exec = ft_check_in_env_2(v, v->l->exec, 0, v->l->arg);
	}
	if (v->nb_cmd != 1)
	{
		tmp = v->l;
		while (tmp)
		{
			if (tmp->arg)
				tmp->arg = ft_check_in_env(v, tmp->arg, 0);
			if (tmp->exec)
				tmp->exec = ft_check_in_env_2(v, tmp->exec, 0, tmp->arg);
			tmp = tmp->next;
		}
	}
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

	if (!ft_check_invalid_signs(str, '<', -1, 0)
		|| !ft_check_invalid_signs(str, '>', -1, 0))
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
	dol_replace(v);
	ft_exec(v, v->l);
	ft_free(v);
	return (1);
}
