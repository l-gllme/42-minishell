/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:19:08 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/23 12:55:53 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_in_out(t_g *v, int nb)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = ft_split(v->tab[nb], ' ');
	if (!tmp)
	{
		ft_putstr_fd("Malloc Error in ft_parse_command\n", 2);
		return (-1);
	}
	if (ft_strncmp(tmp[0], "<", ft_strlen(tmp[0])) == 0)
	{
		v->in = 1;
		v->file_in = ft_strdup(ft_suppr_dq_sq(tmp[1]));
	}
	while (tmp[++i])
		;
	if (i > 2 && tmp[i - 2][0] == '>' && tmp[i - 2][1] == 0)
	{
		v->out = 1;
		v->file_out = ft_strdup(ft_suppr_dq_sq(tmp[i - 1]));
	}
	free_char_tab(tmp);
	return (1);
}
