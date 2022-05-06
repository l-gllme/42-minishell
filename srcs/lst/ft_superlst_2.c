/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superlst_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:31:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:32:31 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
