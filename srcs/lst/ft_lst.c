/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:42:13 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/20 16:19:17 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if ((*alst))
	{
		tmp = ft_lstlast(*alst);
		tmp->next = new;
	}
	else
	{
		*alst = new;
	}
}

void	del(void *data)
{
	free(data);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdelone(list, del);
		list = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		(*del)(lst->content);
	if (lst->name)
		(*del)(lst->name);
	if (lst->line)
		(*del)(lst->line);
	free(lst);
}

t_list	*ft_lstnew(char	*name, char *content, char *line)
{
	t_list	*tmp;

	tmp = malloc(sizeof(struct s_list));
	if (!tmp)
		return (0);
	tmp->name = name;
	tmp->line = line;
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}
