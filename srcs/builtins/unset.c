/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:51:45 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/25 16:18:41 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_unset(char *arg, t_g *v)
{
	t_list *tmp;
	t_list *temp;

	tmp = v->list;
	
	if (!arg)
		return ;
	if (arg[ft_strlen(arg) - 1] == ' ')
		arg[ft_strlen(arg) - 1] = 0;
	while (tmp->next)
	{
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
			return ;
			
		}
		tmp = tmp->next;
	}
}
