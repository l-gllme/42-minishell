/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_in_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:29:50 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 14:35:04 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_in_no_cmd(char **tab, int choice, t_g *v, t_l *tmp)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	if (!tab)
		return (0);
	while (tab[++i] && choice == 0)
	{
		if (tab[i][0] == '<' && tab[i][1] == 0)
			i++;
		else if (tab[i][0] == '<' && tab[i][1] == '<')
			ft_here_doc_no_cmd(tab[++i], v, tmp, 0);
	}
	i = -1;
	while (tab[++i] && choice == 1)
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			i++;
		else if (tab[i][0] == '<')
			if (!check_valid_infile(tab[++i]))
				return (ft_custom_error(NULL, 0, NULL));
	}
	return (1);
}

void	ft_litlle_close(int fd, int dd)
{
	if (fd != -1)
		close(fd);
	if (dd != -1)
		close(dd);
}

int	check_valid_infile(char *file)
{
	int	dd;
	int	fd;

	ft_suppr_dq_sq(file);
	fd = open(file, O_RDONLY);
	dd = open(file, O_DIRECTORY);
	if (access(file, F_OK))
	{
		g_shell.retour = 1;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (0);
	}
	else if (fd == -1 && dd == -1 && access(file, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" :Permission denied\n", 2);
		return (0);
	}
	else
		ft_litlle_close(fd, dd);
	return (1);
}
