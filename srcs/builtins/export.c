/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:35:14 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/20 13:30:50 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_name(char *split)
{
	int	i;

	if (!split)
		return (0);
	if (ft_isdigit(split[0]))
		return (0);
	i = 0;
	while (split[i])
	{
		if (ft_isalpha(split[i]) || ft_isdigit(split[i]) || split[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_already_in_env(char *split, t_g *v)
{
	t_list	*tmp;

	tmp = v->list;
	if (!split)
		return ;
	while (tmp)
	{
		if (tmp->name && !ft_strcmp(split, tmp->name))
			ft_unset(split, v);
		tmp = tmp->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	**ft_list_to_tab_for_exprt(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->exprt;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	if (!recup)
		return (NULL);
	i = 0;
	while (tmp)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	return (recup);
}

char	**ft_list_to_tab(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->list;
	tmp = tmp->next;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	if (!recup)
		return (NULL);
	i = 0;
	while (tmp)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	return (recup);
}

char	**ft_sort_ascii(char **av)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	while (i != ft_tablen(av))
	{
		j = 0;
		while (j < ft_tablen(av))
		{
			if (ft_strcmp(av[i], av[j]) < 0)
			{
				swap = av[i];
				av[i] = av[j];
				av[j] = swap;
			}
			j++;
		}
		i++;
	}
	return (av);
}

t_list	*tab_to_list(char **env, t_list *list)
{
	int		i;
	char	*name;
	char	*content;
	char	*line;

	name = NULL;
	content = NULL;
	i = -1;
	list = ft_lstnew(NULL, NULL, NULL);
	while (env[++i])
	{
		name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
		if (!name)
			return (NULL);
		if (!ft_recup_name(name, env[i]))
			return (0);
		content = ft_strdup(env[i] + ft_strlen(name));
		line = ft_strdup(env[i]);
		ft_lstadd_back(&list, ft_lstnew(name, content, line));
	}
	return (list);
}

void	ft_export_no_arg(t_g *v)
{
	char	**recup;
	t_list	*list;

	list = NULL;
	recup = ft_list_to_tab(v);
	recup = ft_sort_ascii(recup);
	list = tab_to_list(recup, list);
	list = list->next;
	while (list)
	{
		if (!ft_check_equal(list->line))
			printf("export %s\n", list->name);
		else
			printf("export %s=\"%s\"\n", list->name, list->content + 1);
		list = list->next;
	}
	return ;
}

int	ft_check_equal(char *recup)
{
	int	i;

	i = 0;
	while (recup[i])
	{
		if (recup[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		in_env_sans_dollard(char *str, t_g *v);
char	*ft_recup_content(char *str, t_g *v);

void	ft_put_in_export(char *arg, t_g *v)
{
	if (!in_env_sans_dollard(arg, v) && !ft_recup_content(arg, v))
		ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(arg),
				NULL, ft_strdup(arg)));
	return ;
}

char	*ft_recup_content(char *str, t_g *v)
{
	t_list	*tmp;

	tmp = v->list;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
		{
			return (tmp->content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	in_env_sans_dollard(char *str, t_g *v)
{
	int		i;
	t_list	*tmp;

	i = 0;
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

char	*ft_recup_correct_export(char *str)
{
	int		i;
	char	*recup;

	i = 0;
	while (str[i] != '+' && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		i++;
	}
	recup = malloc(sizeof(char) * (i + 1));
	if (!recup)
		return (NULL);
	i = 0;
	while (str[i] != '+' && str[i])
	{
		recup[i] = str[i];
		i++;
	}
	recup[i] = 0;
	return (recup);
}

void	ft_export_plus_equal_2(t_g *v, char *recup, char *arg)
{
	char	*test;
	char	*line;

	line = NULL;
	test = ft_strdup(recup);
	if (!ft_recup_content(recup, v))
	{
		line = ft_strjoin_gnl(test, ft_strdup(arg + ft_strlen(test) + 1));
		ft_unset(recup, v);
		ft_lstadd_back(&v->list, ft_lstnew(recup,
				ft_strdup(arg + ft_strlen(recup) + 1), line));
	}
	else
	{
		printf("coucou\n");
		recup = ft_strdup(test);
		line = ft_strjoin_gnl(line, ft_recup_content(recup, v));
		recup = ft_strdup(test);
		line = ft_strjoin_gnl(line, ft_strdup(arg + ft_strlen(recup) + 2));
		line = ft_strjoin(recup, line);
		recup = ft_strdup(test);
		ft_already_in_env(recup, v);
		ft_lstadd_back(&v->list, ft_lstnew(recup,
				ft_strdup(line + ft_strlen(recup)), line));
	}
}

void	ft_export_no_in_env(char *recup, char *line, t_g *v, char *arg)
{
	line = ft_strjoin_gnl(line, recup);
	line = ft_strjoin(line, arg + ft_strlen(recup) + 1);
	ft_lstadd_back(&v->list, ft_lstnew(recup,
			ft_strdup(arg + ft_strlen(recup) + 1), line));
}

void	ft_export_plus_equal_no_content(char *recup, t_g *v, char *line)
{
	line = ft_strjoin(recup, "=""");
	ft_lstadd_back(&v->list, ft_lstnew(recup,
			ft_strdup(line + ft_strlen(recup)), line));
}

int	ft_export_plus_equal(char *arg, t_g *v)
{
	int		i;
	char	*line;
	char	*recup;

	i = 0;
	line = NULL;
	recup = ft_recup_correct_export(arg);
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=' && arg[i - 1] != '+')
		{
			if (!in_env_sans_dollard(recup, v))
			{
				if (arg[ft_strlen(arg) - 1] == '=')
					ft_export_plus_equal_no_content(recup, v, line);
				else
					ft_export_no_in_env(recup, line, v, arg);
			}
			else
				ft_export_plus_equal_2(v, recup, arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_memcpy(const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	char		*cpydest;
	const char	*cpysrc;

	if (!src)
		return (NULL);
	i = 0;
	if (n <= 0)
		return (NULL);
	dest = malloc(sizeof(char) * (n + 1));
	cpydest = dest;
	cpysrc = src;
	while (i < n)
	{
		cpydest[i] = cpysrc[i];
		i++;
	}
	cpydest[i] = 0;
	dest = cpydest;
	return (dest);
}

void	ft_normal_export(t_g *v, char **split, char **recup, int i)
{
	ft_already_in_env(split[0], v);
	if (recup[i][ft_strlen(recup[i]) - 1] == '=')
	{
		if (!ft_check_name(ft_memcpy(recup[i], ft_strlen(recup[i]) - 1)))
			printf("Minishell: export: '%s': not a valid identifier\n",
				recup[i]);
		else
			ft_lstadd_back(&v->list, ft_lstnew(split[0], NULL, recup[i]));
	}
	else
	{
		ft_suppr_dq_sq(recup[i]);
		split = ft_split(recup[i], '=');
		split[1] = ft_strjoin("=", split[1]);
		if (!ft_check_name(split[0]))
			printf("Minishell: export: '%s': not a valid identifier\n",
				recup[i]);
		else
			ft_lstadd_back(&v->list, ft_lstnew(split[0], split[1], recup[i]));
	}
}

void	ft_export_3(char **recup, int i, t_g *v)
{
	if (!ft_check_name(recup[i]))
		printf("Minishell: export: '%s': not a valid identifier\n",
			recup[i]);
	else
		ft_put_in_export(recup[i], v);
}

void	ft_export(char *arg, t_g *v)
{
	char	**recup;
	char	**split;
	int		i;

	i = 0;
	if (!arg)
	{
		ft_export_no_arg(v);
		return ;
	}
	recup = ft_supersplit(arg, ' ');
	while (recup[i])
	{
		split = ft_split_by_string(recup[i], "+=");
		if (!ft_check_name(split[0]) || (recup[i][0] == '+'
			&& recup[i][1] == '=') || recup[i][0] == '=')
			printf("Minishell: export: '%s': not a valid identifier\n",
				recup[i]);
		else if (!ft_check_equal(recup[i]))
			ft_export_3(recup, i, v);
		else if (!ft_export_plus_equal(recup[i], v))
			ft_normal_export(v, split, recup, i);
		i++;
	}
}
