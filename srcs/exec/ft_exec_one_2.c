/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_one_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:04:05 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/09 14:15:43 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_recup_arg_one(t_f *in_fork, t_l *tmp)
{
	int	i;

	i = -1;
	in_fork->srt = ft_strjoin(tmp->exec, " ");
	in_fork->srt = ft_strjoin_gnl(in_fork->srt, tmp->arg);
	in_fork->toto = ft_supersplit(in_fork->srt, ' ');
	while (in_fork->toto[++i])
		ft_suppr_dq_sq(in_fork->toto[i]);
	free(in_fork->srt);
}

void	ft_one_error(t_l *tmp, t_g *v, t_f *in_fork)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->name_in, 2);
	ft_putstr_fd(" :Permission denied\n", 2);
	ft_lstclear(&v->list, &free);
	free_char_tab(in_fork->toto);
	free(in_fork->str);
	ft_free(v);
	exit(1);
}

void	ft_one_str_null(t_g *v, t_f *in_fork)
{
	ft_lstclear(&v->list, &free);
	ft_free(v);
	free_char_tab(in_fork->toto);
	exit(127);
}

void	ft_out_tab_one(t_f *in_fork, t_g *v, t_l *tmp)
{
	if (!ft_exec_out(v, tmp))
	{
		ft_lstclear(&v->list, &free);
		free_char_tab(in_fork->toto);
		free(in_fork->str);
		ft_free(v);
		exit(1);
	}
	if (tmp->name_out)
	{
		if (tmp->append)
			in_fork->fd = open(tmp->name_out, O_WRONLY | O_APPEND, 0644);
		else
			in_fork->fd = open(tmp->name_out, O_WRONLY | O_TRUNC, 0644);
		dup2(in_fork->fd, STDOUT_FILENO);
		close(in_fork->fd);
	}
}
