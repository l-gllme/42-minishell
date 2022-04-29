/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/29 16:40:24 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_here_doc_no_cmd(char *limiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			return (1);
		if (str[0] != 0 && str && ft_strcmp(str, limiter) == 0)
		{
			free(str);
			return (1);
		}
		free(str);
	}
	return (1);
}

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

int	ft_exec_in_no_cmd(char **tab)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	if (!tab)
		return (0);
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == 0)
			i++;
		else if (tab[i][0] == '<' && tab[i][1] == '<')
			ft_here_doc_no_cmd(tab[++i]);
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

int	ft_exec_in(t_g *v, t_l *tmp)
{
	(void)v;
	if (!tmp->exec)
	{
		ft_exec_in_no_cmd(tmp->in_tab);
	}
	else
	{
		return (0);
	}
	return (0);
}

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;

	tmp = l;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp);
		/*if (tmp->out_tab != NULL)
			ft_exec_out(v, tmp);
		if (tmp->exec != NULL)
			ft_exec_cmd(v, tmp);
		*/tmp = tmp->next;
	}
	return (1);
}
