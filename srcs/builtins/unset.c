/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:51:45 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:16:39 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	cut_unset(char *arg, t_list *tmp)
{
	t_list	*temp;

	if (!ft_strncmp(arg, tmp->next->name, ft_strlen(arg)))
	{
		if (tmp->next->name)
			free(tmp->next->name);
		if (tmp->next->content && ft_strlen(tmp->next->content) > 0)
			free(tmp->next->content);
		if (tmp->next->line && ft_strlen(tmp->next->line) > 0)
			free(tmp->next->line);
		temp = tmp->next->next;
		if (tmp->next)
			free(tmp->next);
		tmp->next = temp;
		return (0);
	}
	return (1);
}

void	ft_unset(char *arg, t_g *v)
{
	t_list	*tmp;

	tmp = v->list;
	if (!arg)
		return ;
	if (arg[ft_strlen(arg) - 1] == ' ')
		arg[ft_strlen(arg) - 1] = 0;
	while (tmp->next)
	{
		if (!cut_unset(arg, tmp))
			return ;
		tmp = tmp->next;
	}
}
