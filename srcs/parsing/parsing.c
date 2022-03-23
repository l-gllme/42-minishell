/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/23 15:05:11 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parse_command(t_g *v, int nb)
{
	if (!ft_check_in_out(v, nb))
		return (-1);
	return (1);
}

int	parse_cmd(t_g *v)
{
	int	i;

	i = -1;
	while (v->tab[++i])
		;
	if (i == 1)
	{
		if (!ft_parse_command(v, 0))
			return (-1);
	}
	else if (i > 1)
	{
		ft_putstr_fd("Multiple commands\n", 1);
	}
	return (1);
}

void	init_struct(char **tab, t_g *v)
{
	v->tab = tab;
	v->file_in = NULL;
	v->file_out = NULL;
	v->arg = NULL;
	v->out = 0;
	v->in = 0;
}

int	parsing(char *str, t_g *v)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (-1);
	if (!get_cmd(str, tab))
		return (-1);
	if (!check_not_closed_pipes(tab))
		return (-1);
	init_struct(tab, v);
	if (!parse_cmd(v))
		return (-1);
	i = -1;
	while (tab[++i])
	{
	//	printf("i:%d = %s\n", i, tab[i]);
		free(tab[i]);
	}
	free(tab);
	return (1);
}
