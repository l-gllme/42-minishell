/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:07:05 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/11 18:10:20 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fork_error(t_l *tmp, t_g *v, char **toto, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->name_in, 2);
	ft_putstr_fd(" :Permission denied\n", 2);
	ft_lstclear(&v->list, &free);
	free_char_tab(toto);
	free(str);
	ft_free(v);
	exit(1);
}

void	ft_fork_str_null(int pipe_fd[2], t_g *v, char **toto, t_f *in_fork)
{
	(void)in_fork;
	close(pipe_fd[1]);
	if (v->fd_tmp)
		close(v->fd_tmp);
	ft_lstclear(&v->list, &free);
	ft_free(v);
	free_char_tab(toto);
	g_shell.retour = 127;
	in_fork->value = 127;
	exit(in_fork->value);
}

void	ft_out_tab_fork(t_f *in_fork, t_g *v, t_l *tmp)
{
	if (!ft_exec_out(v, tmp))
	{
		ft_lstclear(&v->list, &free);
		if (!ft_is_builtin(tmp->exec, v, 0, tmp))
		{
			free_char_tab(in_fork->toto);
			free(in_fork->str);
		}
		ft_free(v);
		g_shell.retour = 1;
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

void	ft_recup_arg_fork(t_f *in_fork, t_l *tmp)
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

void	ft_follow_check(t_f *in_fork)
{
	in_fork->fd = open("/dev/null", O_RDONLY);
	dup2(in_fork->fd, 0);
}
