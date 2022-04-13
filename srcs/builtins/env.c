/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:05:43 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/13 17:57:55 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_env(t_g *v)
{
	t_list	*tmp;

	tmp = v->list;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_check_equal(tmp->line))
			tmp = tmp->next;
		else
		{	
			printf("%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
}
