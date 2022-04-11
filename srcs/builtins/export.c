/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:35:14 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/11 19:03:14 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_name(t_g *v)
{
	(void)v;
	return (1);
}

void	ft_export(char *arg, t_g *v)
{
	char	**recup;
	char	**split;
	int		i;

	i = 0;
	ft_suppr_dq_sq(arg);
	if (!arg)
		return ;
	recup = ft_supersplit(arg, ' ');
	while (recup[i])
	{
		split = ft_split(recup[i], '=');
		split[i + 1] = ft_strjoin("=", split[i + 1]);
		if (!ft_check_name(v))
			return ;
		ft_lstadd_back(&v->list, ft_lstnew(split[i], split[i + 1], recup[i]));
		i++;
	}
	//ft_env(v);
}
