/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:19:18 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/30 17:37:04 by jtaravel         ###   ########.fr       */
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

int	ft_exec_in_no_cmd(char **tab, int choice, t_g *v)
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
			ft_here_doc_no_cmd(tab[++i], v);
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

char	*try_access(char *cmd, t_g *v)
{
	int		i;
	char	**path;
	char	*s;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(ft_recup_content("PATH", v) + 1, ':');
	i = -1;
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

void	ft_exec_cmd_test(t_l *tmp, t_g *v)
{
	int	frk;
	char	*srt;
	char	**toto;

	if (tmp->arg != NULL)
	{
		srt = ft_strjoin(tmp->exec, " ");
		srt = ft_strjoin_gnl(srt, tmp->arg);
		toto = ft_split(srt, ' ');
		free(srt);
	}
	else
		toto = ft_split(tmp->exec, ' ');
	frk = fork();
	if (frk == 0)
	{
		execve(try_access(tmp->exec, v), toto, v->env);
	}
	else
		wait(NULL);
}


int	ft_exec_in(t_g *v, t_l *tmp, int c)
{
	if (!tmp->exec)
	{
		ft_exec_in_no_cmd(tmp->in_tab, c, v);
	}
	else
	{
		ft_exec_in_no_cmd(tmp->in_tab, c, v);
		ft_exec_cmd_test(tmp, v);
		return (0);
	}
	return (0);
}
