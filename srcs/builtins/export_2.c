/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:24:00 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:25:19 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	**ft_sort_ascii(char **av)
{
	int		i;
	int		j;
	int		len;
	char	*swap;

	len = ft_tablen(av);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
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
	ft_lstdelone(list, &free);
	list = list->next;
	while (list)
	{
		if (!ft_check_equal(list->line))
			printf("export %s\n", list->name);
		else
			printf("export %s=\"%s\"\n", list->name, list->content + 1);
		ft_lstdelone(list, &free);
		list = list->next;
	}
	free_char_tab(recup);
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
	if (!in_env_sans_dollard(arg, v) && !ft_recup_content(arg, v))
		ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(arg),
				NULL, ft_strdup(arg)));
	return ;
}
