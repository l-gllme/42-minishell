/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/18 16:29:49 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_cmd(char *str, char **tab)
{
	int	i;
	int	sq_opened;
	int	dq_opened;
	int	j;
	int	k;
	int	l;

	i = -1;
	j = 0;
	k = 0;
	sq_opened = 0;
	dq_opened = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && dq_opened == 0)
		{
			if (sq_opened)
				sq_opened = 0;
			else
				sq_opened = 1;
		}
		if (str[i] == '"' && sq_opened == 0)
		{
			if (dq_opened)
				dq_opened = 0;
			else
				dq_opened = 1;
		}
		if (((str[i] == '&'&& str[i + 1] == '&') || (str[i] == '|' && str[i - 1] != '|')
				|| (str[i] == '|' && str[i + 1] == '|'))&& !dq_opened && !sq_opened)
		{
			tab[k] = malloc(sizeof(char *) * (i + 1 - j));
			if (!tab[k])
				return (-1);
			l = 0;
			while (j < i)
			{
				tab[k][l] = str[j];
				j++;
				l++;
			}
			tab[k][j] = 0;
			k++;
			j = i;
		}
	}
	tab[k] = malloc(sizeof(char *) * (ft_strlen(str + j) + 1));
	if (!tab[k])
		return (-1);
	i = 0;
	while (str[j])
	{
		tab[k][i] = str[j];
		i++;
		j++;
	}
	tab[k][i] = 0;
	k++;
	tab[k] = 0;
	return (1);
}

static int	count_pipes(char *str)
{
	int	i;
	int	sq_opened;
	int	dq_opened;
	int	cmd_counter;

	i = -1;
	sq_opened = 0;
	dq_opened = 0;
	cmd_counter = 1;
	while (str[++i])
	{
		if (str[i] == '\'' && dq_opened == 0)
		{
			if (sq_opened)
				sq_opened = 0;
			else
				sq_opened = 1;
		}
		if (str[i] == '"' && sq_opened == 0)
		{
			if (dq_opened)
				dq_opened = 0;
			else
				dq_opened = 1;
		}
		if (str[i] == '|' && !dq_opened && !sq_opened)
			cmd_counter++;
	}
	return (cmd_counter + 1);
}
int	parsing(char *str)
{
	char **tab;
	int	i;

	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (-1);
	if (!get_cmd(str, tab))
		return (-1);
	i = -1;
	while (tab[++i])
	{
		//printf("i:%d = %s\n", i, tab[i]);
		free(tab[i]);
	}
	free(tab);
	return (1);
}
