/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:46:08 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 15:22:48 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_in_tab_fork(t_f *in_fork, t_g *v, t_l *tmp)
{
	if (in_fork->fd == -1 && access(tmp->name_in, X_OK))
		ft_fork_error(tmp, v, in_fork->toto, in_fork->str);
	dup2(in_fork->fd, STDIN_FILENO);
	close(in_fork->fd);
	if (v->dup_type != 1)
		close(v->fd_tmp);
}

void	ft_builtins_fork(t_g *v, int pipe_fd[2])
{
	ft_lstclear(&v->list, &free);
	ft_free(v);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(g_shell.retour);
}

void	ft_check_all_fork(t_l *tmp, t_g *v, t_f *in_fork, int pipe_fd[2])
{
	signal(SIGQUIT, handler);
	if (tmp->arg != NULL && !ft_is_builtin(tmp->exec, v, 0, tmp))
		ft_recup_arg_fork(in_fork, tmp);
	else if (!ft_is_builtin(tmp->exec, v, 0, tmp))
		in_fork->toto = ft_split(tmp->exec, ' ');
	if (tmp->name_in)
		ft_in_tab_fork(in_fork, v, tmp);
	else if (v->dup_type != 1)
		dup2(v->fd_tmp, STDIN_FILENO);
	if (tmp->out_tab)
		ft_out_tab_fork(in_fork, v, tmp);
	else if (tmp->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
	}
	if (ft_is_builtin(tmp->exec, v, 1, tmp))
		ft_builtins_fork(v, pipe_fd);
	if (pipe_fd[1] != 0)
		close(pipe_fd[1]);
	else
	{
		in_fork->fd = open("/dev/null", O_RDONLY);
		dup2(in_fork->fd, 0);
	}
}

void	ft_else_fork(t_g *v, t_f *in_fork, int pipe_fd[2])
{
	if (v->dup_type != 1)
		close(v->fd_tmp);
	if (pipe_fd[1] != 0)
		close(pipe_fd[1]);
	free(v->wagon);
	if (WTERMSIG(in_fork->value) == 3)
	{
		printf ("Quit (core dumped)\n");
		g_shell.retour = 131;
	}
}

int	ft_exec_cmd_no_redirect(t_g *v, t_l *tmp, char *str, int pipe_fd[2])
{
	int	frk;
	t_f	in_fork;

	in_fork.str = str;
	if (tmp->name_in)
		in_fork.fd = open(tmp->name_in, 0, 0644);
	in_fork.value = 0;
	g_shell.in_exec = 1;
	frk = fork();
	if (frk == 0)
	{
		ft_check_all_fork(tmp, v, &in_fork, pipe_fd);
		if (str != NULL)
			execve(in_fork.str, in_fork.toto, v->new_env);
		ft_fork_str_null(pipe_fd, v, in_fork.toto);
	}
	ft_else_fork(v, &in_fork, pipe_fd);
	return (1);
}
