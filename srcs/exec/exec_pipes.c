/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:54:41 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/26 16:57:31 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_multiple(t_g *v)
{
	int	frk;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	frk = fork();
	if (frk == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_exec_one(v);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(frk, NULL, 0);
	}
	close(fd[1]);
	close(fd[0]);
}


int	ft_exec_pipes(t_g *v)
{
	/*while (v->nb_cmd != 1)
	{
		ft_exec_multiple(v);	
		v->l = v->l->next;
		v->nb_cmd--;
	}
	ft_exec_multiple(v);
	wait(NULL);
	dup2(STDIN_FILENO, STDOUT_FILENO);*/
	while (v->nb_cmd)
	{
		ft_exec_one(v);
		v->l = v->l->next;
		v->nb_cmd--;
	}
	return (1);
}
