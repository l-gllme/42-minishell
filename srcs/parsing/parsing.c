/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 18:51:28 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_not_followed_sign_in_tab(t_g *v, int i)
{
	while (v->l->in_tab[++i])
	{
		if (v->l->in_tab[i + 1] == 0)
		{
			if (v->l->in_tab[i][0] == '<')
			{
				printf("minishell: syntax error near unexpected token");
				return (ft_custom_error("`newline'\n", 0, v));
			}
		}
		else if (v->l->in_tab[i][0] == '<' && v->l->in_tab[i + 1][0] == '<')
		{
			printf("minishell: syntax error near unexpected token");
			return (ft_custom_error("`< or <<'\n", 0, v));
		}
	}
	return (1);
}

int	ft_check_not_followed_sign_out_tab(t_g *v, int i)
{
	while (v->l->out_tab[++i])
	{
		if (v->l->out_tab[i + 1] == 0)
		{
			if (v->l->out_tab[i][0] == '>')
			{
				printf("minishell: syntax error near unexpected token");
				return (ft_custom_error("`newline'\n", 0, v));
			}
		}
		else if (v->l->out_tab[i][0] == '>'
			&& v->l->out_tab[i + 1][0] == '>')
		{
			printf("minishell: syntax error near unexpected token");
			return (ft_custom_error("`> or >>'\n", 0, v));
		}
	}
	return (1);
}

int	check_not_followed_sign(t_g *v)
{
	int	i;

	i = -1;
	if (v->l->in_tab)
	{
		if (!ft_check_not_followed_sign_in_tab(v, i))
			return (0);
	}
	i = -1;
	if (v->l->out_tab)
	{
		if (!ft_check_not_followed_sign_out_tab(v, i))
			return (0);
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
	int		i;
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

char	*ft_recup_for_retour(char *str, char *recup, int i, char *tmp)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			if (j == 0)
				recup = NULL;
			recup = ft_strjoin_gnl(recup, tmp);
			i += 2;
			j += ft_strlen(tmp);
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

char	*ft_recup_retour(char *str)
{
	int		i;
	char	*tmp;
	char	*recup;

	tmp = ft_itoa(g_shell.retour);
	recup = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp)));
	i = 0;
	if (str[i] == ' ')
		i++;
	recup = ft_recup_for_retour(str, recup, i, tmp);
	return (recup);
}

char	*ft_recup_add_space(char *res, char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
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

char	*ft_add_space_dol(char *str)
{
	int		i;
	int		c;
	char	*res;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
			c++;
		i++;
	}
	res = malloc(sizeof(char) * ((c + i) + 1));
	if (!res)
		return (NULL);
	res = ft_recup_add_space(res, str);
	return (res);
}

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

char	*ft_check_special_3(char *test, int len, char *str, char *res)
{
	free(test);
	test = ft_strdup(str + len);
	res = ft_strjoin_gnl(res, test);
	free(test);
	free(str);
	return (res);
}

char	*ft_check_special_2(t_list *tmp, char *res, char *str, char *test)
{
	int	len;

	len = ft_strlen(test) + 1;
	while (tmp)
	{
		if (!ft_strcmp(test, tmp->name))
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
			break ;
		}
		tmp = tmp->next;
	}
	res = ft_check_special_3(test, len, str, res);
	return (res);
}

char	*ft_check_special(char *str, t_g *v, int i)
{
	int		c;
	char	*res;
	t_list	*tmp;
	char	*test;

	tmp = v->list;
	c = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			&& str[i] != '$' && str[i + 1] != '?' && str[i] != '_')
			break ;
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
	res = ft_check_special_2(tmp, res, str, test);
	return (res);
}

int	parsing(char *str, char **env, t_list *list)
{
	char	**tab;
	t_g		*v;
	int		c;
	t_l		*tmp;

	tmp = NULL;
	if (!ft_check_invalid_signs(str, '<', -1, 0)
		|| !ft_check_invalid_signs(str, '>', -1, 0))
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
