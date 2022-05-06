/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 17:23:55 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_not_followed_sign(t_g *v)
{
	int	i;

	i = -1;
	if (v->l->in_tab)
	{
		while (v->l->in_tab[++i])
		{
			if (v->l->in_tab[i + 1] == 0)
			{
				if (v->l->in_tab[i][0] == '<')
					return (ft_custom_error("minishell: syntax error near unexpected token `newline'\n", 0, v));
			}
			else if (v->l->in_tab[i][0] == '<' && v->l->in_tab[i + 1][0] == '<')
			{
				return (ft_custom_error("minishell: syntax error near unexpected token `< or <<'\n", 0, v));
			}
		}
	}
	i = -1;
	if (v->l->out_tab)
	{
		while (v->l->out_tab[++i])
		{
			if (v->l->out_tab[i + 1] == 0)
			{
				if (v->l->out_tab[i][0] == '>')
					return (ft_custom_error("minishell: syntax error near unexpected token `newline'\n", 0, v));
			}
			else if (v->l->out_tab[i][0] == '>' && v->l->out_tab[i + 1][0] == '>')
					return (ft_custom_error("minishell: syntax error near unexpected token `> or >>'\n", 0, v));
		}
	}
	return (1);
}

void	init_struct(char **tab, t_g *v, char **env, t_list *list)
{
	v->l = malloc(sizeof(t_l));
	v->l->next = NULL;
	v->l->name_in = NULL;
	v->l->name_out = NULL;
	v->tab = tab;
	v->list = list;
	v->env = env;
	v->cmd = NULL;
	v->nb_cmd = 0;
	v->access = 0;
	v->l->in_tab = NULL;
	v->l->out_tab = NULL;
	v->l->exec = NULL;
	v->l->arg = NULL;
	v->fd_in = 0;
	v->file_in = NULL;
	v->urandom = NULL;
	v->retour = 0;
	v->new_env = NULL;
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

int	in_env(char *str, t_g *v)
{
	int	i;
	t_list	*tmp;

	i = 0;
	str = ft_strdup(str + 1);
	tmp = v->list;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	free(str);
	return (0);
}

char	*ft_recup_retour(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*recup;

	tmp = ft_itoa(g_shell.retour);
	recup = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp)));
	i = 0;
	j = 0;
	if (str[i] == ' ')
		i++;
	while (str[i]) 
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			recup = NULL;
			recup = ft_strjoin_gnl(recup, tmp);
			i+=2;
			j+= ft_strlen(tmp);
		}
		else
		{
			recup[j] = str[i];
			i++;
			j++;
		}
	}
	recup[j] = 0;
	free(tmp);
	free(str);
	return (recup);
}

char	*ft_add_space_dol(char *str)
{
	int	i;
	int	c;
	char	*res;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] ==  '$')
			c++;
		i++;
	}
	res = malloc(sizeof(char) * ((c + i) + 1));
	if (!res)
		return (NULL);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')// && str[0] != '$')
		{
			g_shell.retour = 7;
			res[c] = ' ';
			c++;
		}
		res[c] = str[i];
		i++;
		c++;
	}
	res[c] = 0;
	return (res);
}

char	*ft_check_special(char *str, t_g *v);

int	ft_check_doll(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_check_special(char *str, t_g *v)
{
	int	i;
	int	c;
	char	*res;
	t_list	*tmp;
	char	*test;

	tmp = v->list;
	i = 0;
	c = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && !ft_isalpha(str[i])) && str[i] != '$' && str[i + 1] != '?' && str[i] != '_')
			break;
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	if (ft_strlen(str) == ft_strlen(res))
	{
		free(res);
		return (str);
	}
	test = ft_strdup(res + 1);
	while (tmp)
	{
		if (!ft_strcmp(test, tmp->name))// && in_env(str, v))
		{
			if (tmp->content)
			{
				free(res);
				res = ft_strdup(tmp->content + 1);
			}
			else
			{
				free(res);
				res = ft_strdup("");
			}
			break;
		}
		tmp = tmp->next;
	}
	free(test);
	test = ft_strdup(str + i);
	res = ft_strjoin_gnl(res, test);
	free(test);
	free(str);
	return (res);
}

int	parsing(char *str, char **env, t_list *list)
{
	char	**tab;
	t_g	*v;
	int	c;
	t_l	*tmp;

	tmp = NULL;
	if (!ft_check_invalid_signs(str, '<', -1, 0) || !ft_check_invalid_signs(str, '>', -1, 0))
		return (0);
	v = malloc(sizeof(t_g));
	if (!v)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	c = count_pipes(str);
	if (c == 0)
	{
		free(v);
		return (0);
	}
	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	init_struct(tab, v, env, list);
	if (!get_cmd(str, tab))
		return (ft_custom_error(NULL, 0, v));
	if (!check_not_closed_pipes(tab))
		return (ft_custom_error(NULL, 0, v));
	if (!parse_cmd(v))
		return (0);
	if (c - 2 >= v->nb_cmd)
		return (ft_custom_error("invalid syntax!\n", 0, v));
	if (v->nb_cmd == 1)
	{
		if (v->l->arg)
			v->l->arg = ft_check_in_env(v, v->l->arg, 0);
		if (v->l->exec)
			v->l->exec = ft_check_in_env_2(v, v->l->exec, 0, v->l->arg);
		ft_exec(v, v->l);
	}
	if (v->nb_cmd != 1)
	{
		tmp = v->l;
		while (tmp)
		{
			if (tmp->arg)
				tmp->arg = ft_check_in_env(v, tmp->arg, 0);
			if (tmp->exec)
				tmp->exec = ft_check_in_env_2(v, tmp->exec, 0, tmp->arg);
			tmp = tmp->next;
		}
		ft_exec(v, v->l);
	}
	ft_free(v);
	return (1);
}
