/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/27 12:34:22 by jtaravel         ###   ########.fr       */
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
	if (v->env[0])
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
	recup[i] = ft_strdup(tmp->line);
	recup[i + 1] = 0;
	return (recup);
}

static int	cut_exec_one(t_g *v, int choice)
{
	if (choice == 1)
	{
		if (v->l->in_tab != NULL)
			exec_in(v, v->l->in_tab);
		if (v->l->out_tab != NULL)
			exec_out(v, v->l->out_tab);
		ft_is_builtin(v->l->exec, v, 1);
	}
	else if (choice == 2)
	{
		if (v->l->in_tab != NULL)
			redirect_in(v);
		if (v->l->out_tab != NULL)
			redirect_out(v);
		if (v->l->exec != NULL)
			ft_exec_cmd(v);
		if (v->l->in_tab != NULL && v->l->exec != NULL)
			dup2(1, STDIN_FILENO);
		if (v->l->out_tab != NULL && v->l->exec != NULL)
			dup2(0, STDOUT_FILENO);
	}
	return (1);
}

static int	cut_exec_one_fork(t_g *v)
{
	int	frk;
	int	value;

	value = 0;
	frk = fork();
	if (frk == 0)
	{
		if (v->l->in_tab != NULL)
			redirect_in(v);
		if (v->l->out_tab != NULL)
			redirect_out(v);
		if (v->l->exec != NULL)
		{
			value = ft_exec_cmd(v);
			if (v->list)
				ft_lstclear(&v->list, &free);
			if (v && value != 127)
				ft_free(v);
			free(v);
			exit(value);
		}
		if (v->list)
			ft_lstclear(&v->list, &free);
		if (v)
			ft_free(v);
		free(v);
		exit(0);
	}
	else
		waitpid(frk, &value, 0);
	g_retour = WEXITSTATUS(value);
	return (1);
}

void	ft_exec_one(t_g *v)
{
	v->new_env = ft_regroup_env(v);
	if (v->l->exec != NULL && ft_is_builtin(ft_suppr_dq_sq(v->l->exec),
			v, 0) == 2)
		cut_exec_one(v, 1);
	else if (v->l->exec != NULL && ft_is_builtin(v->l->exec, v, 0)
		&& v->l->out_tab == NULL)
		cut_exec_one(v, 2);
	else
		cut_exec_one_fork(v);
	if (v->urandom)
		unlink(v->urandom);
	return ;
}
