/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:35:14 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/12 18:06:14 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_name(char *split)
{
	int	i;

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
	i = 0;
	while (tmp->next)
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
	while (list)
	{
		printf("export %s=\"%s\"\n", list->name, list->content);
		list = list->next;
	}
	return ;
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
	while (recup[i] != NULL)
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
			if (!ft_check_name(split[j]))
			{
				printf("Invalid identifier\n LOUIS FAIT LES FREE ET ERROR CORRECT STP\n");
				return ;
			}
			ft_lstadd_back(&v->list, ft_lstnew(split[j], split[j + 1], recup[i]));
			i++;
			j++;
		}
	}
	//ft_env(v);
}
