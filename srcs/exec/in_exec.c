/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:04:28 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/13 15:37:30 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_infile(char *file)
{
	int	dd;
	int	fd;

	ft_suppr_dq_sq(file);
	fd = open(file, O_RDONLY);
	dd = open(file, O_DIRECTORY);
	if (fd == -1 && dd == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (0);
	}
	else
	{
		if (fd != -1)
			close(fd);
		if (dd != -1)
			close(dd);
	}
	return (1);
}

static int	cut_exec_in_dup(char **tab, int i, int len, int fd)
{
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			i++;
		else if (tab[i][0] == '<')
		{
			if (!check_valid_infile(tab[++i]))
			{
				dup2(STDOUT_FILENO, STDIN_FILENO);
				ft_custom_error(NULL, 0, NULL);
			}
			if (i == len - 1)
			{
				fd = open(tab[i], 0);
				if (fd == -1)
					return (0);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
	}
	return (1);
}

static int	exec_in_dup(t_g *v, char **tab, int i)
{
	int	len;
	int	fd;

	len = ft_tablen(tab);
	fd = 0;
	v->dup_type = 1;
	if (tab[len - 2][0] == '<' && tab[len - 2][1] == 0)
		v->dup_type = 0;
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == 0)
			i++;
		else if (tab[i][0] == '<' && tab[i][1] == '<')
		{
			if (len - 2 == i)
				v->dup_type = 10;
			ft_here_doc(tab[++i], v);
		}
	}
	if (!cut_exec_in_dup(tab, -1, len, fd))
		return (0);
	return (1);
}

int	redirect_in(t_g *v)
{
	if (v->l.exec != NULL)
		exec_in_dup(v, v->l.in_tab, -1);
	else
		exec_in(v, v->l.in_tab);
	return (1);
}

int	exec_in(t_g *v, char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == 0)
			i++;
		else if (tab[i][0] == '<' && tab[i][1] == '<')
			ft_here_doc(tab[++i], v);
	}
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			i++;
		else if (tab[i][0] == '<')
			if (!check_valid_infile(tab[++i]))
				ft_custom_error(NULL, 0, NULL);
	}
	return (1);
}
