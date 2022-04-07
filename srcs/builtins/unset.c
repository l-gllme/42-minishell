/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:51:45 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/07 19:10:34 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_unset(char *arg, t_g *v)
{
	t_list *tmp;

	tmp = v->list;
	
	if (!arg)
		return ;
	while (tmp->next)
	{
		if (!ft_strncmp(arg, tmp->next->name, ft_strlen(arg) - 1))
		{
			free(tmp->next->name);
			free(tmp->next->content);
			free(tmp->next->line);
			free(tmp->next);
			tmp->next = tmp->next->next;
			return ;
			
		}
		tmp = tmp->next;
	}
}
