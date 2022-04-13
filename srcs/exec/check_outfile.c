/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:21:14 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/13 15:22:32 by lguillau         ###   ########.fr       */
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
