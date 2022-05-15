/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:47:13 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/15 18:07:08 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_recup_signal_2(t_f *in_fork)
{
	if (WTERMSIG(in_fork->value) + 128 == 134)
	{
		printf("Aborted (core dumped)\n");
		g_shell.retour = 134;
	}
	if (WTERMSIG(in_fork->value) + 128 == 139)
	{
		printf("Segmentation fault (core dumped)\n");
		g_shell.retour = 139;
	}
	if (WTERMSIG(in_fork->value) + 128 == 135)
	{
		printf("Bus error (core dumped)\n");
		g_shell.retour = 135;
	}
	if (WTERMSIG(in_fork->value) + 128 == 133)
	{
		printf("Trace/breakpoint trap (core dumped)\n");
		g_shell.retour = 133;
	}
	if (WTERMSIG(in_fork->value) + 128 == 132)
	{
		printf("Illegal instruction (core dumped)\n");
		g_shell.retour = 132;
	}
}

void	ft_else_fork_2(t_g *v, int pipe_fd[2])
{
	if (v->dup_type != 1)
		close(v->fd_tmp);
	if (pipe_fd[1] != 0)
		close(pipe_fd[1]);
	free(v->wagon);
}

void	ft_else_fork(t_g *v, t_f *in_fork, int pipe_fd[2])
{
	(void)pipe_fd;
	if (WIFSIGNALED(in_fork->value))
	{
		ft_recup_signal_2(in_fork);
		if (WTERMSIG(in_fork->value) + 128 > 139)
			printf("Signal\n");
	}
	if (WEXITSTATUS(in_fork->value) == 1 && v->dup_type == v->nb_cmd)
		g_shell.retour = 1;
	if (WEXITSTATUS(in_fork->value) == 2 && v->dup_type == v->nb_cmd)
		g_shell.retour = 2;
	if (WTERMSIG(in_fork->value) == 3)
	{
		printf ("Quit (core dumped)\n");
		g_shell.retour = 131;
	}
	else if (WTERMSIG(in_fork->value) + 128 == 130)
	{
		write(1, "\n", 1);
		g_shell.retour = 130;
	}
	ft_else_fork_2(v, pipe_fd);
}
