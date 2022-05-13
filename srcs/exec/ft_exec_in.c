/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:19:18 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/13 16:18:37 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cut_exec_in_dup(char **tab, int i, t_l *tmp)
{
	int	len;
	int	fd;

	len = ft_tablen(tab);
	while (tab[++i])
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
			i++;
		else if (tab[i][0] == '<')
		{
			if (!check_valid_infile(tab[++i]))
				ft_custom_error(NULL, 0, NULL);
			if (i == len - 1)
			{
				fd = open(tab[i], 0);
				if (fd != -1)
					tmp->in = fd;
				tmp->name_in = ft_strdup(tab[i]);
				close(fd);
			}
		}
	}
	return (1);
}

void	ft_exec_in_dup_2(t_g *v, char **tab, t_l *tmp, int i)
{
	int	len;

	len = ft_tablen(tab);
	if (tab[i][0] == '<' && tab[i][1] == 0)
		return ;
	else if (tab[i][0] == '<' && tab[i][1] == '<')
	{
		if (len - 2 == i)
			v->dup_type = 10;
		ft_here_doc_no_cmd(tab[++i], v, tmp, 0);
	}
}

int	ft_exec_in_dup(t_g *v, char **tab, t_l *tmp, int choice)
{
	int	len;
	int	fd;
	int	i;

	i = 0;
	if (!tab)
		return (0);
	len = ft_tablen(tab);
	fd = 0;
	if (choice == 0)
	{
		while (tab[i])
		{
			ft_exec_in_dup_2(v, tab, tmp, i);
			i++;
		}
	}
	if (choice == 1)
	{
		if (!cut_exec_in_dup(tab, -1, tmp))
			return (0);
	}
	return (1);
}

char	*try_access(char *cmd, t_g *v, int i)
{
	char	**path;
	char	*s;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(ft_recup_content("PATH", v) + 1, ':');
	while (path[++i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd);
	}
	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
		{
			s = ft_strdup(path[i]);
			free_char_tab(path);
			return (s);
		}
	}
	free_char_tab(path);
	return (NULL);
}

int	ft_exec_in(t_g *v, t_l *tmp, int c)
{
	if (tmp->exec == NULL)
	{
		ft_exec_in_no_cmd(tmp->in_tab, c, v, tmp);
		if (g_shell.retour == 130)
		{
			free(tmp->exec);
			tmp->exec = NULL;
			return (0);
		}
	}
	else
	{
		ft_exec_in_dup(v, tmp->in_tab, tmp, c);
		if (g_shell.retour == 130)
		{
			free(tmp->exec);
			tmp->exec = NULL;
			return (0);
		}
		return (0);
	}
	return (0);
}
