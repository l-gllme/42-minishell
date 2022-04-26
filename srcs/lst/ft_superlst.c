/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:54:29 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/26 13:57:50 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_super_lstclear(t_l **lst, void (*del)(void *))
{
	t_l	*list;
	t_l	*tmp;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_super_lstdelone(list, del);
		list = tmp;
	}
	*lst = NULL;
}

void	ft_super_lstdelone(t_l *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->in_tab)
		(*del)(lst->in_tab);
	if (lst->out_tab)
		(*del)(lst->out_tab);
	if (lst->exec)
		free(lst->exec);
	if (lst->arg)
		free(lst->arg);
	free(lst);
}

t_l	*ft_super_lstnew(char **out_tab, char **in_tab, char *arg, char *exec)
{
	t_l	*tmp;

	tmp = malloc(sizeof(struct s_list));
	if (!tmp)
		return (0);
	tmp->out_tab = out_tab;
	tmp->in_tab = in_tab;
	tmp->arg = arg;
	tmp->exec = exec;
	tmp->next = NULL;
	return (tmp);
}

void	ft_super_lstadd_back(t_l **alst, t_l *new)
{
	t_l	*tmp;

	tmp = *alst;
	if ((*alst))
	{
		tmp = ft_super_lstlast(*alst);
		tmp->next = new;
	}
	else
	{
		*alst = new;
	}
}

t_l	*ft_super_lstlast(t_l *lst)
{
	t_l	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

int	ft_super_lstsize(t_l *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
