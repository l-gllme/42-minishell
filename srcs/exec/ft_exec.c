/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:08:00 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/25 16:19:31 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_exec_3(t_l *l, t_l *tmp, int pipe_fd[2], t_g *v)
{
	if (l->next == NULL && ft_is_builtin(l->exec, v, 0, tmp))
		ft_exec_builtin(v, tmp);
	else if (v->nb_cmd == 1)
		ft_exec_cmd_lol(v, tmp, 1, pipe_fd);
	else
	{
		if (v->dup_type != 1)
			v->fd_tmp = pipe_fd[0];
		if (tmp->next != NULL)
			pipe(pipe_fd);
		ft_exec_cmd_lol(v, tmp, 0, pipe_fd);
	}
}

void	ft_exec_2(t_g *v, t_l *tmp, t_l *l)
{
	int	pipe_fd[2];

	tmp = l;
	v->fd_tmp = 0;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 1);
		if (tmp->out_tab != NULL && tmp->exec == NULL)
			ft_exec_out(v, tmp);
		if (tmp->exec != NULL)
		{
			ft_suppr_dq_sq(tmp->exec);
			v->dup_type++;
			ft_exec_3(l, tmp, pipe_fd, v);
		}
		if (tmp->name_in != NULL)
		{
			if (tmp->in_tab[ft_tablen(tmp->in_tab) - 2][1] != 0)
				unlink(tmp->name_in);
		}
		tmp = tmp->next;
	}
	if (v->fd_tmp)
		close(v->fd_tmp);
}

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;

	g_shell.in_exec = 0;
	tmp = l;
	v->dup_type = 0;
	v->new_env = ft_regroup_env(v);
	while (tmp)
	{
		tmp->in = -1;
		tmp->out = -1;
		tmp->name_in = NULL;
		tmp->name_out = NULL;
		v->dup_type = 0;
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 0);
		tmp = tmp->next;
	}
	ft_exec_2(v, tmp, l);
	while (v->nb_cmd && l->next != NULL)
	{
		wait (NULL);
		v->nb_cmd--;
	}
	return (1);
}
