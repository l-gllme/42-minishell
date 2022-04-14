/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:35:14 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/14 17:52:53 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_name(char *split, t_g *v)
{
	int	i;
	t_list	*tmp;

	tmp = v->list;
	if (!split)
		return (1);
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
	while (tmp)
	{
		if (!ft_strncmp(split, tmp->name, ft_strlen(split)))
			ft_unset(split, v);
		tmp = tmp->next;
	}
	return (1);
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

t_list  *tab_to_list(char **env, t_list *list)
{
        int             i;
        char    *name;
        char    *content;
        char    *line;

        name = NULL;
        content = NULL;
        i = -1;
        list = ft_lstnew(NULL, NULL, NULL);
        while(env[++i])
        {
                name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
		if (!name)
			return (NULL);
                if (!ft_recup_name(name, env[i]))
                        return (0);
                content = ft_strdup(env[i] + ft_strlen(name) + 1);
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
			printf("export %s=\"%s\"\n", list->name, list->content);
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

void	ft_put_in_export(char *arg, t_g *v)
{
	ft_check_name(arg, v);
	ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(arg), NULL, ft_strdup(arg)));
	return ;
}

int	ft_check_plus_equal(char *str)
{
	(void)str;
	return (0);
}	

void	ft_export_plus_equal(char *arg, t_g *v)
{
	(void)arg;
	(void)v;
}

void	ft_export(char *arg, t_g *v)
{
	char	**recup;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!arg)
	{
		ft_export_no_arg(v);
		return ;
	}
	recup = ft_supersplit(arg, ' ');
	while (recup[i])
	{
		if (ft_check_plus_equal(recup[i]))
		{
			ft_export_plus_equal(recup[i], v);
			i++;
		}
		if (!ft_check_equal(recup[i]))
		{
			ft_put_in_export(recup[i], v);
			i++;
		}
		else
		{
			if (recup[i][ft_strlen(recup[i]) - 1] == '=')
			{
				ft_lstadd_back(&v->list, ft_lstnew(recup[i], NULL, recup[i]));
				i+=2;
			}
			else
			{
				ft_suppr_dq_sq(recup[i]);
				split = ft_split(recup[i], '=');
				split[j + 1] = ft_strjoin("=", split[j + 1]);
				if (!ft_check_name(split[j], v))
				{
					printf("Invalid identifier\n LOUIS FAIT LES FREE ET ERROR CORRECT STP\n");
					return ;
				}
				ft_lstadd_back(&v->list, ft_lstnew(split[j], split[j + 1], recup[i]));
				i++;
				j++;
			}
		}	
	}
}
