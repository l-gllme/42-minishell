/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/25 18:09:54 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_not_followed_sign(t_g *v)
{
	int	i;

	i = -1;
	if (v->l.in_tab)
	{
		while (v->l.in_tab[++i])
		{
			if (v->l.in_tab[i + 1] == 0)
			{
				if (v->l.in_tab[i][0] == '<')
					return (ft_custom_error("minishell: syntax error near unexpected token `newline'\n", 0, v));
			}
			else if (v->l.in_tab[i][0] == '<' && v->l.in_tab[i + 1][0] == '<')
			{
				return (ft_custom_error("minishell: syntax error near unexpected token `< or <<'\n", 0, v));
			}
		}
	}
	i = -1;
	if (v->l.out_tab)
	{
		while (v->l.out_tab[++i])
		{
			if (v->l.out_tab[i + 1] == 0)
			{
				if (v->l.out_tab[i][0] == '>')
					return (ft_custom_error("minishell: syntax error near unexpected token `newline'\n", 0, v));
			}
			else if (v->l.out_tab[i][0] == '>' && v->l.out_tab[i + 1][0] == '>')
					return (ft_custom_error("minishell: syntax error near unexpected token `> or >>'\n", 0, v));
		}
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
		if (!check_not_followed_sign(v))
			return (ft_custom_error(NULL, 0, NULL));
	}
	else if (i > 1)
	{
		v->nb_cmd = i;
		i = -1;

		if (!ft_add_spaces(v, '<', 0) || !ft_add_spaces(v, '>', 0))
			return (ft_custom_error(NULL, 0, v));
		while (v->tab[++i])
			printf("%s\n",v->tab[i]);
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
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_recup_retour(char *str)
{
	int		i;
	char	*tmp;
	char	*recup;

	tmp = ft_itoa(g_retour);
	recup = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp)));
	i = 0;
	while (str[i]) 
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			recup = ft_strjoin(recup, tmp);
			i+=2;
		}
		else
		{
			recup[i] = str[i];
			i++;
		}
	}
	return (recup);
}

char	*ft_check_in_env_2(t_g *v)
{
	char	*recup;
	char	**split;
	int		i;
	int		d;
	int		c;
	char	*name;
	t_list	*tmp;
	char	*test;

	int	l = 0;
	i = 0;
	d = 0;
	c = 0;
	recup = NULL;
	if (v->l.exec)
	{
		l = 1;
		split = ft_supersplit(v->l.exec, ' ');
		free(v->l.exec);

	}
	else
		return (NULL);	
	while (split[i] && l == 1 && split[i][0] == '$')
	{
		c = 1;
		split[i] = ft_recup_retour(split[i]);
		ft_suppr_dq_sq(split[i]);
		if (split[i][0] == '$' && split[i][1] == '$' && split[i][3] == 0)
			break;
		if (split[i][0] == '$' && split[i][1] == 0)
			break;
		while (split[i][ft_strlen(split[i]) - 1] == '$' && ft_strlen(split[i]) != 1)
		{
			split[i][ft_strlen(split[i]) -1] = '\0';
			d++;
		}
		tmp = v->list;
		tmp = tmp->next;
		while (tmp && split[i][0] == '$')
		{
			name = ft_strjoin("$", tmp->name);
			test = ft_strdup(split[i]);
			if (!ft_strncmp(split[i], name, ft_strlen(split[i])) && in_env(split[i], v))
			{
				if (tmp->content)
					split[i] = ft_strdup(tmp->content + 1);
				else
					split[i] = ft_strdup("");
				break;
			}
			else if (!in_env(test, v))
					split[i] = ft_strdup("");
			tmp = tmp->next;
			free(name);
		}
		i++;
	}
	i = 0;
	while (split[i])
	{
		recup = ft_strjoin_gnl(recup, split[i]); 
		if (d)
		{
			recup = ft_strjoin(recup, "$");
			d--;
		}
		if (split[i + 1])
			recup = ft_strjoin_gnl(recup, " "); 
		i++;
	}
	if (recup[ft_strlen(recup) - 1] == ' ')
		recup[ft_strlen(recup) - 1] = 0;
	free_char_tab(split);
	return (recup);
}

char	*ft_check_in_env(t_g *v)
{
	char	*recup;
	char	**split;
	int		i;
	int		d;
	int		c;
	char	*name;
	t_list	*tmp;
	char	*test;

	int	l = 0;
	i = 0;
	d = 0;
	c = 0;
	recup = NULL;
	if (v->l.arg)
	{
		l = 1;
		split = ft_supersplit(v->l.arg, ' ');
		free(v->l.arg);

	}
	else
		return (NULL);	
	while (split[i] && l == 1 && split[i][0] == '$')
	{
		c = 1;
		split[i] = ft_recup_retour(split[i]);
		ft_suppr_dq_sq(split[i]);
		if (split[i][0] == '$' && split[i][1] == '$' && split[i][3] == 0)
			break;
		if (split[i][0] == '$' && split[i][1] == 0)
			break;
		while (split[i][ft_strlen(split[i]) - 1] == '$' && ft_strlen(split[i]) != 1)
		{
			split[i][ft_strlen(split[i]) -1] = '\0';
			d++;
		}
		tmp = v->list;
		tmp = tmp->next;
		while (tmp && split[i][0] == '$')
		{
			name = ft_strjoin("$", tmp->name);
			test = ft_strdup(split[i]);
			if (!ft_strncmp(split[i], name, ft_strlen(split[i])) && in_env(split[i], v))
			{
				if (tmp->content)
					split[i] = ft_strdup(tmp->content + 1);
				else
					split[i] = ft_strdup("");
				break;
			}
			else if (!in_env(test, v))
					split[i] = ft_strdup("");
			tmp = tmp->next;
			free(name);
		}
		i++;
	}
	i = 0;
	while (split[i])
	{
		recup = ft_strjoin_gnl(recup, split[i]); 
		if (d)
		{
			recup = ft_strjoin(recup, "$");
			d--;
		}
		if (split[i + 1])
			recup = ft_strjoin_gnl(recup, " "); 
		i++;
	}
	if (recup[ft_strlen(recup) - 1] == ' ')
		recup[ft_strlen(recup) - 1] = 0;
	free_char_tab(split);
	return (recup);
}

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

t_list	*ft_change_shlvl(t_list *list, char **env)
{
	int		tmp;
	int		c;
	char	*tmp_str;

	c = 0;
	tmp = 0;
	(void)env;
	if (list == NULL)
		list = list->next;
	while (list->next)
	{
		if (ft_strncmp(list->name, "SHLVL", 5) == 0)
		{
			c = 1;
			tmp = ft_atoi(list->line + 6) + 1;
			tmp_str = ft_itoa(tmp);
			free(list->content);
			free(list->name);
			free(list->line);
			list->name = ft_strdup("SHLVL");
			list->content = ft_strjoin("=", tmp_str);
			list->line = ft_strjoin("SHLVL=", tmp_str);
			free(tmp_str);
		}
		list = list->next;
	}
	if (ft_strncmp(list->name, "SHLVL", 5) == 0)
	{
		c = 1;
		tmp = ft_atoi(list->line + 6) + 1;
		tmp_str = ft_itoa(tmp);
		free(list->content);
		free(list->name);
		free(list->line);
		list->name = ft_strdup("SHLVL");
		list->content = ft_strjoin("=", tmp_str);
		list->line = ft_strjoin("SHLVL=", tmp_str);
		free(tmp_str);
	}
	if (c == 0)
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1"), ft_strdup("SHLVL=1")));
	return (list);
}

t_list	*ft_replace_pwd(t_list *list)
{
	int	c;
	char	*line;

	c = 0;
	while (list->next)
	{
		if (ft_strcmp(list->name, "PWD") == 0)
			return (list);
		list = list->next;
	}
	if (ft_strcmp(list->name, "PWD") == 0)
		return (list);
 	line = getcwd(NULL, 0);
	if (c == 0)
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("PWD"), ft_strjoin("=", line), ft_strjoin("PWD=", line)));
	free(line);
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
	list = ft_lstnew(ft_strdup("toto"), ft_strdup("toto"), ft_strdup("toto"));
	while(env[++i])
	{
		name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
		if (!ft_recup_name(name, env[i]))
			return (0);
		content = ft_strdup(env[i] + ft_strlen(name));
		line = ft_strdup(env[i]);
		ft_lstadd_back(&list, ft_lstnew(name, content, line));
	}
	if (i == 0)
	{
 		line = getcwd(NULL, 0);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1"), ft_strdup("SHLVL=1")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("PWD"), ft_strjoin("=", line), ft_strjoin("PWD=", line)));
		free(line);
	}
	else
	{
		ft_change_shlvl(list, env);
		ft_replace_pwd(list);
	}
	return (list);
}
int	parsing(char *str, char **env, t_list *list)
{
	char	**tab;
	t_g	*v;
	int	c;

	if (!ft_check_invalid_signs(str, '<') || !ft_check_invalid_signs(str, '>'))
		return (0);
	v = malloc(sizeof(t_g));
	if (!v)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	c = count_pipes(str);
	if (c == 0)
		return (0);
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
	if (v->l.arg)
		v->l.arg = ft_check_in_env(v);
	if (v->l.exec)
		v->l.exec = ft_check_in_env_2(v);
	if (v->nb_cmd == 1)
		ft_exec_one(v);
	ft_free(v);
	return (1);
}
