/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:19:08 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/29 17:13:44 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_len(t_g *v, char c, int k, int len)
{
	int	i;
	t_s	s;

	i = 0;
	init_syntax_struct(&s);
	while (v->tab[k][i])
	{
		check_sq_dq(&s, v->tab[k][i]);
		if (s.sq_opened == 0 && s.dq_opened == 0 && i != 0 && v->tab[k][i] == c)
		{
			if (v->tab[k][i - 1] != ' ' || v->tab[k][i - 1] != c)
				len++;
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[k][i] == c && v->tab[k][i + 1] == c)
		{
			i++;
			len++;
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[k][i] == c && c && v->tab[k][i + 1] != c)
			len++;
		i++;
	}
	len += ft_strlen(v->tab[k]);
	return (len);
}

static int	cut_add_space(t_g *v, char c, int k, int j)
{
	int	i;
	t_s	s;

	i = 0;
	init_syntax_struct(&s);
	while (v->tab[k][i])
	{
		check_sq_dq(&s, v->tab[k][i]);
		if (s.sq_opened == 0 && s.dq_opened == 0 && i != 0 && v->tab[k][i] == c)
		{
			if (v->tab[k][i - 1] != ' ' || v->tab[k][i - 1] != c)
				v->wagon[j++] = ' ';
		}
		v->wagon[j] = v->tab[k][i];
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[k][i] == c && v->tab[k][i + 1] == c)
		{
			v->wagon[j] = c;
			j++;
			i++;
			v->wagon[j] = ' ';
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[k][i] == c && v->tab[k][i + 1] != c)
		{
			v->wagon[j] = c;
			j++;
			v->wagon[j] = ' ';
		}
		j++;
		i++;
	}
	v->wagon[j] = 0;
	return (1);
}

int	ft_add_spaces(t_g *v, char c, int index)
{
	int	len;

	len = count_len(v, c, index, 0);
	v->wagon = malloc(sizeof(char *) * (len + 1));
	if (!v->wagon)
	{
		ft_putstr_fd("Malloc error in ft_add_space()", 2);
		return (0);
	}
	cut_add_space(v, c, index, 0);
	free(v->tab[index]);
	v->tab[index] = ft_strdup(v->wagon);
	free(v->wagon);
	v->wagon = NULL;
	return (1);
}
