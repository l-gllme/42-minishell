/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:15:15 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/05 17:16:32 by jtaravel         ###   ########.fr       */
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

static int	cut_check_outfile(char *file, int type)
{
	int	fd;

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

int	check_outfile(char *file, int type)
{
	int	dd;

	ft_suppr_dq_sq(file);
	dd = open(file, O_DIRECTORY);
	if (dd != -1)
	{
		close(dd);
		return (error_out_file(file, "Is a directory"));
	}
	if (!(cut_check_outfile(file, type)))
		return (0);
	return (1);
}

int	check_dup_outfile(char *file, int type)
{
	int	fd;

	if (!check_outfile(file, type))
		return (0);
	if (type == 1)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_custom_error("open error in check_outfile()\n", 0, NULL));
	}
	if (type == 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (ft_custom_error("open error in check_outfile()\n", 0, NULL));
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_custom_error("dup2 error in check_outfile()\n", 0, NULL);
	close(fd);
	return (1);
}


int	exec_out_dup(t_g *v, char **tab)
{
	int	i;
	int	len;
	int	type;


	i = -1;
	len = ft_tablen(tab);
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '>' && tab[i][1] == 0 && i != len - 2)
		{
			type = 1;
			if (!check_outfile(tab[i + 1], 1))
				return (ft_custom_error(NULL, 0, v));
		}
		else if (tab[i][0] == '>' && tab[i][1] == '>' && i != len - 2)
		{
			type = 0;
			if (!check_outfile(tab[i + 1], 0))
				return (ft_custom_error(NULL, 0, v));
		}
		if (i == len - 1)
		{
			if (tab[i - 1][1] == 0)
				type = 1;
			else
				type = 0;
			check_dup_outfile(tab[i], type);
		}
	}
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
