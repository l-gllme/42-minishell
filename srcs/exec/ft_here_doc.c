/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:17:54 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/12 15:36:09 by lguillau         ###   ########.fr       */
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

static void	ft_here_doc_no_cmd(char *limiter)
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

static int	create_tmp_file(t_g *v)
{
	int		dev;
	char	random[11];

	dev = open("/dev/urandom", O_RDONLY);
	if (dev == -1)
		return (ft_custom_error("open error in create_tmp_file()\n", 0, NULL));
	read(dev, random, 10);
	random[10] = 0;
	v->urandom = ft_strjoin(".tmp_file", random);
	if (!v->urandom)
		return (ft_custom_error("strjoin error in create_tmp_file()\n",
				0, NULL));
	return (1);
}

static int	cut_here_doc(t_g *v, char *limiter)
{
	char	*str;

	v->tmp_file = open(v->urandom, O_CREAT | O_WRONLY, 0644);
	if (v->tmp_file == -1)
		return (ft_custom_error("open error in ft_here_doc()\n", 0, v));
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
	return (1);
}

int	ft_here_doc(char *limiter, t_g *v)
{
	int		fd;

	ft_suppr_dq_sq(limiter);
	if (v->l.exec == NULL)
	{
		ft_here_doc_no_cmd(limiter);
		return (1);
	}
	if (!create_tmp_file(v))
		return (ft_custom_error(NULL, 0, v));
	if (!cut_here_doc(v, limiter))
		return (ft_custom_error(NULL, 0, v));
	if (v->dup_type == 10)
	{
		fd = open(v->urandom, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	return (1);
}
