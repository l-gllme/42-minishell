/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/12 16:06:57 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/random.h>

char	**ft_regroup_env(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->list;
	tmp = tmp->next;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (tmp->next)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	return (recup);
}

void	ft_exec_one(t_g *v)
{
	int	frk;

	v->new_env = ft_regroup_env(v);
	if (v->l.exec != NULL && ft_is_builtin(ft_suppr_dq_sq(v->l.exec), v, 0) == 2)
	{
		if (v->l.in_tab != NULL)
			exec_in(v, v->l.in_tab);
		if (v->l.out_tab != NULL)
			exec_out(v, v->l.out_tab);
		ft_is_builtin(v->l.exec, v, 1);
	}
	else if (v->l.exec != NULL && ft_is_builtin(v->l.exec, v, 0)
		&& v->l.out_tab == NULL)
	{
		if (v->l.in_tab != NULL)
			redirect_in(v);
		if (v->l.out_tab != NULL)
			redirect_out(v);
		if (v->l.exec != NULL)
			ft_exec_cmd(v);
		if (v->l.in_tab != NULL && v->l.exec != NULL)
			dup2(1, STDIN_FILENO);
		if (v->l.out_tab != NULL && v->l.exec != NULL)
			dup2(0, STDOUT_FILENO);
	}
	else
	{
		frk = fork();
		if (frk == 0)
		{
			if (v->l.in_tab != NULL)
				redirect_in(v);
			if (v->l.out_tab != NULL)
				redirect_out(v);
			if (v->l.exec != NULL)
				ft_exec_cmd(v);
			exit(0);
		}
		else
			wait(NULL);
	}
	if (v->urandom)
		unlink(v->urandom);
	return ;
}
