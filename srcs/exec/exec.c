/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/05 16:06:19 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/random.h>

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

void	ft_here_doc_no_cmd(char *limiter)
{
	char	*str;

	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	while (str && hd_cmp(str, limiter) != 0)
	{
		free(str);
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
	}
	get_next_line(42);
	free(str);
}

int	ft_here_doc(char *limiter, t_g *v)
{
	char	*str;
	char	random[11];
	int	dev;
	int	fd;

	ft_suppr_dq_sq(limiter);
	dev = open("/dev/urandom", O_RDONLY);
	read(dev, random, 10);
	random[10] = 0;
	v->urandom = ft_strjoin(".tmp_file", random);
	if (v->l.exec == NULL)
	{
		ft_putstr_fd(v->l.exec, 0);
		ft_here_doc_no_cmd(limiter);
		return (1);
	}
	v->tmp_file = open(v->urandom, O_CREAT | O_WRONLY, 0644);
	if (v->tmp_file == -1)
	{
		ft_putstr_fd("Error tmp_file in ft_here_doc()\n", 2);
		return (0);
	}
	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	while (str && hd_cmp(str, limiter) != 0)
	{
		ft_putstr_fd(str, v->tmp_file);
		ft_putstr_fd("\n", v->tmp_file);
		free(str);
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
	}
	get_next_line(42);
	free(str);
	if (v->dup_type == 10)
	{
		fd = open(v->urandom, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	return (1);
}

void	ft_exec_one(t_g *v)
{
	//int	fd;


	if (v->l.in_tab != NULL)
		redirect_in(v);
	if (v->l.out_tab != NULL)
		redirect_out(v);
	if (v->l.exec != NULL)
		ft_exec_cmd(v);
	//fd = open(v->urandom, O_RDONLY);
	//dup2(fd, STDIN_FILENO);
	dup2(STDOUT_FILENO, STDIN_FILENO);
	if (v->urandom)
		unlink(v->urandom);
	return ;
}
