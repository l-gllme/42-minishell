/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:39:34 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 18:06:05 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_in_tab_one(t_f *in_fork, t_g *v, t_l *tmp)
{
	in_fork->fd = open(tmp->name_in, 0, 0644);
	if (in_fork->fd == -1 && access(tmp->name_in, X_OK))
		ft_one_error(tmp, v, in_fork);
	dup2(in_fork->fd, STDIN_FILENO);
	close(in_fork->fd);
}

void	ft_after_fork_one(t_f *in_fork)
{
	if (WTERMSIG(in_fork->value) == 3)
	{
		printf ("Quit (core dumped)\n");
		g_shell.retour = 131;
	}
	else
		g_shell.retour = WEXITSTATUS(in_fork->value);
	free_char_tab(in_fork->toto);
}

void	ft_fork_one(t_l *tmp, t_f *in_fork, t_g *v)
{
	signal(SIGQUIT, handler);
	if (tmp->name_in)
		ft_in_tab_one(in_fork, v, tmp);
	if (tmp->out_tab)
		ft_out_tab_one(in_fork, v, tmp);
}

int	ft_exec_one_cmd(t_g *v, char *str, t_l *tmp)
{
	int		frk;
	t_f		in_fork;

	in_fork.value = 0;
	g_shell.in_exec = 1;
	if (v->l->arg != NULL)
		ft_recup_arg_one(&in_fork, tmp);
	else
		in_fork.toto = ft_split(v->l->exec, ' ');
	frk = fork();
	if (frk == 0)
	{
		ft_fork_one(tmp, &in_fork, v);
		if (str != NULL)
			execve(str, in_fork.toto, v->new_env);
		ft_one_str_null(v, &in_fork);
	}
	else
		waitpid(frk, &in_fork.value, 0);
	ft_after_fork_one(&in_fork);
	return (WEXITSTATUS(in_fork.value));
}
