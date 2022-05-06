/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:58 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:26:57 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

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

void	ft_export_plus_equal_3(t_g *v, char *recup, char *arg, char *test)
{
	char	*tmp;
	char	*line;

	line = NULL;
	recup = ft_strdup(test);
	line = ft_strjoin_gnl(line, ft_recup_content(recup, v));
	free(recup);
	recup = ft_strdup(test);
	tmp = ft_strdup(arg + ft_strlen(recup) + 2);
	line = ft_strjoin_gnl(line, tmp);
	free(tmp);
	tmp = ft_strdup(line);
	free(line);
	line = ft_strjoin(recup, tmp);
	free(tmp);
	free(recup);
	recup = ft_strdup(test);
	ft_already_in_env(recup, v);
	ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(recup),
			ft_strdup(line + ft_strlen(recup)), ft_strdup(line)));
	free(recup);
}

void	ft_export_plus_equal_2(t_g *v, char *recup, char *arg)
{
	char	*test;
	char	*line;
	char	*tmp;

	line = NULL;
	test = ft_strdup(recup);
	if (!ft_recup_content(recup, v))
	{
		tmp = ft_strdup(arg + ft_strlen(test) + 1);
		line = ft_strjoin(test, tmp);
		free(tmp);
		ft_unset(recup, v);
		ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(recup),
				ft_strdup(arg + ft_strlen(recup) + 1), ft_strdup(line)));
	}
	else
		ft_export_plus_equal_3(v, recup, arg, test);
	free(line);
	free(test);
}
