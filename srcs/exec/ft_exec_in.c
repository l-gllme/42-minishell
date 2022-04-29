/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:19:18 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/29 17:31:06 by lguillau         ###   ########.fr       */
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

int	ft_exec_in_no_cmd(char **tab, int choice)
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
			ft_here_doc_no_cmd(tab[++i]);
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

int	ft_exec_in(t_g *v, t_l *tmp, int c)
{
	(void)v;
	if (!tmp->exec)
	{
		ft_exec_in_no_cmd(tmp->in_tab, c);
	}
	else
	{
		//ft_exec_in_cmd(tmp->in_tab, c)
		return (0);
	}
	return (0);
}
