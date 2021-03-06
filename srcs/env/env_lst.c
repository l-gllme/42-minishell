/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:24:22 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:40:40 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static t_list	*ft_replace_pwd(t_list *list)
{
	int		c;
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
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("PWD"),
				ft_strjoin("=", line), ft_strjoin("PWD=", line)));
	free(line);
	return (list);
}	

static void	cut_init_lst(char **env, t_list *list, int i)
{
	char	*line;

	if (i == 0)
	{
		line = getcwd(NULL, 0);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("SHLVL"),
				ft_strdup("1"), ft_strdup("SHLVL=1")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("PWD"),
				ft_strjoin("=", line), ft_strjoin("PWD=", line)));
		free(line);
	}
	else
	{
		ft_change_shlvl(list, env);
		ft_replace_pwd(list);
	}
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
	while (env[++i])
	{
		name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
		if (!ft_recup_name(name, env[i]))
			return (0);
		content = ft_strdup(env[i] + ft_strlen(name));
		line = ft_strdup(env[i]);
		ft_lstadd_back(&list, ft_lstnew(name, content, line));
	}
	cut_init_lst(env, list, i);
	return (list);
}
