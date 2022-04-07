/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/07 20:35:07 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/random.h>

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

void	ft_here_doc_no_cmd(char *limiter)
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

int	ft_here_doc(char *limiter, t_g *v)
{
	char	*str;
	char	random[11];
	int	dev;
	int	fd;

	ft_suppr_dq_sq(limiter);
	dev = open("/dev/urandom", O_RDONLY);
	read(dev, random, 10);
	random[10] = 0;
	v->urandom = ft_strjoin(".tmp_file", random);
	if (v->l.exec == NULL)
	{
		ft_putstr_fd(v->l.exec, 0);
		ft_here_doc_no_cmd(limiter);
		return (1);
	}
	v->tmp_file = open(v->urandom, O_CREAT | O_WRONLY, 0644);
	if (v->tmp_file == -1)
	{
		ft_putstr_fd("Error tmp_file in ft_here_doc()\n", 2);
		return (0);
	}
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
	if (v->dup_type == 10)
	{
		fd = open(v->urandom, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	return (1);
}

int	ft_is_builtin(char *str, t_g *v)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	{
		v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
	{
		v->nb_built++;
		return (2);
	}
	if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
	{
		v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
	{
		v->nb_built++;
		return (1);
	}
	return (0);
}

void	ft_shlvl(t_g *v)
{
	(void)v;
	return ;
}

char	**ft_regroup_env(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int	len;
	int	i;

	tmp = v->list;
	tmp = tmp->next;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	i = 0;
	if (!ft_strncmp(v->l.exec, "./minishell", ft_strlen(v->l.exec)))
		ft_shlvl(v);
	while (tmp->next)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	return (recup);
}

void	ft_exec_one(t_g *v)
{
	int	frk;

	v->new_env = ft_regroup_env(v);
	if (v->l.exec != NULL && ft_is_builtin(ft_suppr_dq_sq(v->l.exec), v) == 2)
	{
		if (v->l.in_tab != NULL)
			exec_in(v, v->l.in_tab);
		if (v->l.out_tab != NULL)
			exec_out(v, v->l.out_tab);
		ft_exec_builtin(v->l.exec, v);
	}
	else if (v->l.exec != NULL && ft_is_builtin(v->l.exec, v) && v->l.out_tab == NULL)
	{
		if (v->l.in_tab != NULL)
			redirect_in(v);
		if (v->l.out_tab != NULL)
			redirect_out(v);
		if (v->l.exec != NULL)
			ft_exec_cmd(v);
		if (v->l.in_tab != NULL && v->l.exec != NULL)
			dup2(1, STDIN_FILENO);
		if (v->l.out_tab != NULL && v->l.exec != NULL)
			dup2(0, STDOUT_FILENO);
	}
	else
	{
		frk = fork();
		if (frk == 0)
		{
			if (v->l.in_tab != NULL)
				redirect_in(v);
			if (v->l.out_tab != NULL)
				redirect_out(v);
			if (v->l.exec != NULL)
				ft_exec_cmd(v);
			exit(0);
		}
		else
			wait(NULL);
	}
	if (v->urandom)
		unlink(v->urandom);
	return ;
}
