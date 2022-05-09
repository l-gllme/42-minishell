/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:31:15 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 15:40:58 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_syntax_struct(t_s *s)
{
	s->dq_opened = 0;
	s->sq_opened = 0;
}

void	check_sq_dq(t_s *s_s, char c)
{
	if (c == '\'' && s_s->dq_opened == 0)
	{
		if (s_s->sq_opened == 0)
			s_s->sq_opened = 1;
		else
			s_s->sq_opened = 0;
	}
	if (c == '"' && s_s->sq_opened == 0)
	{
		if (s_s->dq_opened == 0)
			s_s->dq_opened = 1;
		else
			s_s->dq_opened = 0;
	}
}

static char	*cut_sds(char *str, t_s *s, int i, int c)
{
	int	j;

	j = i - 1;
	if (c == 1)
	{
		if (s->sq_opened)
			s->sq_opened = 0;
		else
			s->sq_opened = 1;
		while (str[++j])
			str[j] = str[j + 1];
	}
	if (c == 2)
	{
		if (s->dq_opened)
			s->dq_opened = 0;
		else
			s->dq_opened = 1;
		while (str[++j])
			str[j] = str[j + 1];
	}
	str[j] = 0;
	return (str);
}

char	*ft_suppr_dq_sq(char *str)
{
	int	i;
	t_s	*s;

	s = malloc(sizeof(t_s));
	init_syntax_struct(s);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && s->dq_opened == 0)
		{
			str = cut_sds(str, s, i, 1);
			i--;
		}
		else if (str[i] == '"' && s->sq_opened == 0)
		{
			str = cut_sds(str, s, i, 2);
			i--;
		}
	}
	free(s);
	return (str);
}
