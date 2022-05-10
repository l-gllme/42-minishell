/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:42:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/10 12:14:18 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_change_shlvl(t_list *list, int c)
{
	int		tmp;
	char	*tmp_str;

	tmp = 0;
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
	return (c);
}

t_list	*ft_change_shlvl(t_list *list, char **env)
{
	int		tmp;
	int		c;

	c = 0;
	tmp = 0;
	(void)env;
	if (list == NULL)
		list = list->next;
	while (list)
	{
		c = cut_change_shlvl(list, c);
		list = list->next;
	}
	if (c == 0)
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("SHLVL"),
				ft_strdup("1"), ft_strdup("SHLVL=1")));
	return (list);
}
