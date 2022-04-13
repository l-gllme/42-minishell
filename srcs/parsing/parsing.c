/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/13 19:14:49 by jtaravel         ###   ########.fr       */
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

void	init_struct(char **tab, t_g *v, char **env, t_list *list)
{
	v->tab = tab;
	v->list = list;
	v->env = env;
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

char	**ft_check_in_env(t_g *v)
{
	int	i;
	int	j;
	int	c;
	char	**recup;
	int	d;

	if (!v->l.arg)
		return (0);
	recup = ft_supersplit(v->l.arg, ' ');
	c = 0;
	d = 0;
	i = 0;
	while (recup[i])
	{
		j = 0;
		while (recup[i][j])
		{
			if (recup[i][j] == '$' && recup[i][j + 1] == '$' && recup[i][j + 2] == 0)
				break;
			if (recup[i][j] == '$' && recup[i][j + 1] == 0)
				break;
			while (recup[i][ft_strlen(recup[i]) - 1] == '$' && ft_strlen(recup[i]) != 1)
			{
				recup[i][ft_strlen(recup[i]) - 1] = '\0';
				d++;
			}
			if (recup[i][j] == '$' && (ft_isdigit(recup[i][j + 1]) || ft_isalpha(recup[i][j + 1]) || recup[i][j + 1] == '_'))
			{
				if (recup[i][j] == '$' && getenv(recup[i] + 1))
				{
					while (!ft_strfind(v->env[c], recup[i] + 1, ft_strlen(recup[i])))
						c++;
					recup[i] = ft_strdup(v->env[c] + ft_strlen(recup[i]));
				}
				else if (recup[i][j] == '$' && !getenv(recup[i] + 1) && ft_strlen(recup[i]) != 1)
				{
					if (d == 0 && ft_strlen(recup[i]) != 1)
						recup[i] = "";
				}
				if (recup[i][j] == '$' && getenv(recup[i] + 2))
				{
					while (!ft_strfind(v->env[c], recup[i] + 2, ft_strlen(recup[i])))
						c++;
					recup[i] = ft_strdup(v->env[c] + ft_strlen(recup[i]));
				}
				else if (recup[i][j] == '$' && !getenv(recup[i] + 2) && ft_strlen(recup[i]) != 1)
				{
					if (d == 0 && ft_strlen(recup[i]) != 1)
						recup[i] = "";
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	free(v->l.arg);
	while (recup[i])
	{
		v->l.arg = ft_strjoin(v->l.arg, recup[i]);
		if (d)
		{
			v->l.arg = ft_strjoin(v->l.arg, "$");
			d--;
		}	
		//printf("recup = %s\n", v->l.arg);
		v->l.arg = ft_strjoin(v->l.arg, " ");
		i++;
	}
	return (0);
}
	/*i = 0;
	c = 0;
	if (!v->l.arg)
	{
		j = 0;
		if (v->cmd[i][0] == '$')
		{
			while (!ft_strfind(v->env[i], v->cmd[j] + 1, ft_strlen(v->cmd[j])))
				i++;
			v->l.exec = ft_strdup(v->env[i] + ft_strlen(v->l.exec));
			return (v->cmd);
		}
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
	printf("recup = %s\n", recup);
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
					free(v->l.arg);
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
}*/

int	ft_lststrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_recup_name(char *name, char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}	
	name[i] = 0;
	return (1);
}

t_list	*ft_change_shlvl(t_list *list)
{
	int	tmp;
	int	c;

	c = 0;
	tmp = 0;
	while (list->next)
	{
		if (ft_strncmp(list->name, "SHLVL", 5) == 0)
		{
			c = 1;
			tmp = ft_atoi(list->line + 6) + 1;
			list->line = ft_strjoin("SHLVL=", ft_itoa(tmp));
		}
		list = list->next;
	}
	if (c == 0)
		ft_lstadd_back(&list, ft_lstnew("SHLVL", "1", "SHLVL=1"));
	return (list);
}

t_list	*init_lst(char **env, t_list *list)
{
	int		i;
	char	*name;
	char	*content;
	char	*line;

	name = NULL;
	content = NULL;
	i = -1;
	list = ft_lstnew(NULL, NULL, NULL);
	while(env[++i])
	{
		name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
		if (!ft_recup_name(name, env[i]))
			return (0);
		content = ft_strdup(env[i] + ft_strlen(name));
		line = ft_strdup(env[i]);
		ft_lstadd_back(&list, ft_lstnew(name, content, line));
	}
	ft_change_shlvl(list);
	return (list);
}
int	parsing(char *str, char **env, t_list *list, t_list *exprt)
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
	init_struct(tab, v, env, list);
	v->exprt = exprt;
	if (!get_cmd(str, tab))
		return (ft_custom_error(NULL, 0, v));
	if (!check_not_closed_pipes(tab))
		return (ft_custom_error(NULL, 0, v));
	if (!parse_cmd(v))
		return (0);
	v->cmd = ft_check_in_env(v);
	if (v->nb_cmd == 1)
		ft_exec_one(v);
	return (1);
}
