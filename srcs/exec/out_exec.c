/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:15:15 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/05 16:18:46 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_out_file(char *file, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	check_outfile(char *file, int type)
{
	int	fd;
	int	dd;

	ft_suppr_dq_sq(file);
	dd = open(file, O_DIRECTORY);
	if (dd != -1)
	{
		close(dd);
		return (error_out_file(file, "Is a directory"));
	}
	if (type == 1)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(file, F_OK) == -1)
			return (ft_custom_error("open error in check_outfile()\n", 0, NULL));
		if (fd == -1)
			return (error_out_file(file, "Permission denied"));
		close(fd);
	}
	else if (type == 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(file, F_OK) == -1)
			return (ft_custom_error("open error in check_outfile()\n", 0, NULL));
		if (fd == -1)
			return (error_out_file(file, "Permission denied"));
		close(fd);
	}
	return (1);
}

int	exec_out_dup(t_g *v, char **tab)
{
	(void)v;
	(void)tab;
	return (1);
}

int	redirect_out(t_g *v)
{
	if (v->l.exec != NULL)
		exec_out_dup(v, v->l.out_tab);
	else
		exec_out(v, v->l.out_tab);
	return (1);
}

int	exec_out(t_g *v, char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '>' && tab[i][1] == 0)
		{
			if (!check_outfile(tab[i + 1], 1))
				return (ft_custom_error(NULL, 0, v));
		}
		else if (tab[i][0] == '>' && tab[i][1] == '>')
		{
			if (!check_outfile(tab[i + 1], 0))
				return (ft_custom_error(NULL, 0, v));
		}

	}
	return (1);
}

	

