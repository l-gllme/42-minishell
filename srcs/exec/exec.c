/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/24 17:58:47 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	hd_cmp(char *s1, char *s2)
{
	int	i;

	i = ft_strlen(s1);
	s1[i - 1] = 0;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_here_doc(char *limiter)
{
	int	fd[2];
	int	frk;
	char	*str;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe error in ft_here_doc()\n", 2);
		return (-1);
	}
	frk = fork();
	if (frk == -1)
	{
		ft_putstr_fd("fork error in ft_here_doc()\n", 2);
		return (-1);
	}
	if (frk == 0)
	{
		close(fd[0]);
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		while (str && hd_cmp(str, limiter) != 0)
		{
			ft_putstr_fd(str, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(str);
			ft_putstr_fd("> ", 1);
			str = get_next_line(0);
		}
		get_next_line(42);
		free(str);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (!dup2(fd[0], STDIN_FILENO))
		{
			ft_putstr_fd("dup2 error in ft_here_doc()\n", 2);
			return (-1);
		}
		wait(NULL);
	}
	return (1);
}

void	ft_exec_one(t_g *v)
{
	(void)v;
	ft_here_doc("toto");
	return ;
}
