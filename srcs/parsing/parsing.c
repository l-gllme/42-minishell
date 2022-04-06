/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/06 11:24:27 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_not_followed_sign(char *str)
{
	t_s	s;
	int	i;

	i = ft_strlen(str);
	init_syntax_struct(&s);
	check_sq_dq(&s, str[i]);
	while (str[--i] == ' ' && !s.sq_opened && !s.dq_opened)
		;
	if (str[i] == '>' || str[i] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}

int	parse_cmd(t_g *v)
{
	int	i;

	i = -1;
	while (v->tab[++i])
		;
	if (i == 1)
	{
		if (!ft_add_spaces(v, '<', 0) || !ft_add_spaces(v, '>', 0))
			return (ft_custom_error(NULL, 0, v));
		if (!check_not_followed_sign(v->tab[0]))
			return (ft_custom_error(NULL, 0, v));
		v->nb_cmd = 1;
		v->cmd = ft_supersplit(v->tab[0], ' ');
		if (!v->cmd)
			return (ft_custom_error("error in ft_supersplit()\n", 0, v));
		if (!stock_in(v))
			return (ft_custom_error("malloc error in stock_in()\n", 0, v));
		if (!stock_out(v))
			return (ft_custom_error("malloc error in stock_in()\n", 0, v));
		if (!stock_exec(v))
			return (ft_custom_error("error in stock_exec()\n", 0, v));
		if (!stock_arg(v))
			return (ft_custom_error("error in stock_arg()\n", 0, v));
	}
	else if (i > 1)
	{
		v->nb_cmd = i;
		return (ft_custom_error("Multiple commands\n", 0, v));
	}
	return (1);
}

void	init_struct(char **tab, t_g *v, char **env)
{
	v->env = env;
	v->tab = tab;
	v->cmd = NULL;
	v->nb_cmd = 0;
	v->access = 0;
	v->l.in_tab = NULL;
	v->l.out_tab = NULL;
	v->l.exec = NULL;
	v->l.arg = NULL;
	v->fd_in = 0;
	v->file_in = NULL;
	v->urandom = NULL;
}

char	**ft_check_in_env(t_g *v)
{
	int	i;
	int	j;
	int	c;
	char	*recup;

	i = 0;
	c = 0;
	if (!v->l.arg)
	{
		j = 0;
		while (!ft_strfind(v->env[i], v->cmd[j] + 1, ft_strlen(v->cmd[j])))
			i++;
		v->l.exec = ft_strdup(v->env[i] + ft_strlen(v->l.exec));
		return (v->cmd);
	}
	i = 0;
	while (v->cmd[i])
	{
		j = 0;
		while (v->cmd[i][j])
		{
			if (v->cmd[i][j] == '$')
			{
				while (v->cmd[i][j] != ' ' && v->cmd[i][j])
				{
					j++;
					c++;
				}
			}
			j++;
		}
		i++;
	}
	recup = malloc(sizeof(char) * (c + 2));
	if (!recup)
		return (NULL);
	i = 0;
	c = 0;
	while (v->cmd[i])
	{
		j = 0;
		while (v->cmd[i][j])
		{
			if (v->cmd[i][j] == '$')
			{
				while (v->cmd[i][j] != ' ' && v->cmd[i][j])
				{
					recup[c] = v->cmd[i][j];
					c++;
					j++;
				}
			}
			j++;
		}
		i++;
	}
	recup[c] = '=';
	recup[c + 1] = '\0';
	i = 0;
	while (!ft_strfind(v->env[i], recup + 1, ft_strlen(recup)))
		i++;
	recup = ft_strdup(v->env[i] + ft_strlen(recup) - 1);
	i = 0;
	c = 0;
	while (v->cmd[i])
	{
		j = 0;
		while (v->cmd[i][j])
		{
			if (v->cmd[i][j] == '$')
			{
				while (recup[c])
				{
					v->l.arg[c] = recup[c];
					c++;
					j++;
				}
			}
			j++;
		}
		i++;
	}
	return (v->cmd);
}

int	parsing(char *str, char **env)
{
	char	**tab;
	t_g	*v;

	if (!ft_check_invalid_signs(str, '<') || !ft_check_invalid_signs(str, '>'))
		return (0);
	v = malloc(sizeof(t_g));
	if (!v)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	init_struct(tab, v, env);
	if (!get_cmd(str, tab))
		return (ft_custom_error(NULL, 0, v));
	if (!check_not_closed_pipes(tab))
		return (ft_custom_error(NULL, 0, v));
	if (!parse_cmd(v))
		return (0);
//	v->cmd = ft_check_in_env(v);
	if (v->nb_cmd == 1)
		ft_exec_one(v);
	return (1);
}
