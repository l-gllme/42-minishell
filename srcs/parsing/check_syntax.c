/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:16:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 18:25:02 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cut_cncp(char **tab, int j, int c, int i)
{
	j = -1;
	c = 0;
	while (tab[i][++j])
	{
		if (tab[i][j] == '|' && j == 0)
		{
			j++;
			if (ft_strlen(tab[i]) == 1)
				return (-1);
		}
		if (tab[i][j] != ' ' && tab[i][j] != '\0' && tab[i][j] != '\n')
			c = 1;
	}
	return (c);
}

/* Check for invalid pipes */

int	check_not_closed_pipes(char **tab)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (tab[++i])
	{
		res = cut_cncp(tab, 0, 0, i);
		if (res == 0 || res == -1)
		{
			g_shell.retour = 2;
			ft_putstr_fd("Invalid syntax\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	cut_cp(char str, t_s *s)
{
	if (str == '\'' && s->dq_opened == 0)
	{
		if (s->sq_opened)
			s->sq_opened = 0;
		else
			s->sq_opened = 1;
	}
	if (str == '"' && s->sq_opened == 0)
	{
		if (s->dq_opened)
			s->dq_opened = 0;
		else
			s->dq_opened = 1;
	}
	if (str == '|' && !s->dq_opened && !s->sq_opened)
		return (1);
	return (0);
}

int	ft_check_invalid_signs(char *str, char c)
{
	int	i;
	int	count;
	t_s	s;

	i = -1;
	init_syntax_struct(&s);
	count = 0;
	while (str[++i])
	{
		check_sq_dq(&s, str[i]);
		if (str[i] == c && s.dq_opened == 0 && s.sq_opened == 0)
		{
			while (str[i] == c)
			{
				count++;
				if (count == 3)
				{
					g_shell.retour = 2;
					return (ft_custom_error("Invalid syntax near << or >>\n", 0, NULL));
				}
				if (str[i + 1] != 0)
					i++;
			}
		}
		count = 0;
	}
	return (1);
}

int	count_pipes(char *str)
{
	int	i;
	int	cmd_counter;
	t_s	*s;

	i = -1;
	s = malloc(sizeof(t_s));
	if (!s)
	{
		ft_putstr_fd("Malloc error in count_pipes()\n", 2);
		return (0);
	}
	init_syntax_struct(s);
	cmd_counter = 1;
	while (str[++i])
		cmd_counter += cut_cp(str[i], s);
	if (s->sq_opened || s->dq_opened)
	{
		ft_putstr_fd("Invalid syntax\n", 2);
		g_shell.retour = 2;
		free(s);
		return (0);
	}
	free(s);
	return (cmd_counter + 1);
}
