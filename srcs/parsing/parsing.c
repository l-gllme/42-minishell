/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/21 16:35:02 by lguillau         ###   ########.fr       */
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
		if (((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i - 1] != '|')
				|| (str[i] == '|' && str[i + 1] == '|')) && !dq_opened && !sq_opened)
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
	if (sq_opened || dq_opened)
	{
		ft_putstr_fd("Invalid syntax\n", 2);
		return (-1);
	}
	return (cmd_counter + 1);
}

int	check_not_closed_sq(char **tab)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		c = 0;
		while (tab[i][++j])
		{
			if (tab[i][j] == '|' && j == 0)
			{
				j++;
				if (ft_strlen(tab[i]) == 1)
				{
					ft_putstr_fd("Invalid syntax\n", 2);
					return (-1);
				}
			}

			if (tab[i][j] != ' ' && tab[i][j] != '\0' && tab[i][j] != '\n')
				c = 1;
		}
		if (c == 0)
		{
			ft_putstr_fd("Invalid syntax\n", 2);
			return (-1);
		}
	}
	return (1);
}

int	ft_reverse_chevron(char **str)
{
	int	file;

	file = open(str[1], O_RDONLY);
	if (file == -1)
		printf("error file\n");
	if (dup2(file, STDIN_FILENO) == -1)
	{
		printf("ERROR DUP\n");
		exit(0);
	}
	return (2);
}

void	ft_suppr_dq_sq(char *str)
{
	int	i;
	int	dq_opened;
	int	sq_opened;

	sq_opened = 0;
	dq_opened = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && dq_opened == 0)
		{
			if (sq_opened)
				sq_opened = 0;
			else
				sq_opened = 1;
			str[i] = 127;
		}
		if (str[i] == '"' && sq_opened == 0)
		{
			if (dq_opened)
				dq_opened = 0;
			else
				dq_opened = 1;
			str[i] = 127;
		}
	}
}

int	ft_is_builtin(char *s,  char **cmd)
{
	if (ft_strncmp(s, "echo", ft_strlen(s)) == 0 && ft_strlen(s) == 4)
	{
		dup2(STDOUT_FILENO, STDIN_FILENO);
		ft_echo(cmd[0]);
	}
	return (1);
}

void	ft_exec_one_command(t_g *v)
{
	int	i;
	//int	frk;

	//frk = fork();
	i = 0;
	//if (frk == -1)
	//	printf("fork error\n");
	//if (frk == 0)
	//{
		v->cmd = ft_split(v->tab[0], ' ');
		if (!v->cmd)
			printf("error tab\n");
		if (v->cmd[0][0] == '<')
			i = ft_reverse_chevron(v->cmd);
		ft_suppr_dq_sq(v->cmd[i]);
		ft_is_builtin(v->cmd[i], v->tab);
	//		exit(0);
	//}//
}
void	parse_cmd(t_g *v)
{
	int	i;

	i = -1;
	while (v->tab[++i])
		;
	if (i == 1)
		ft_exec_one_command(v);
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
	if (!check_not_closed_sq(tab))
		return (-1);
	v->tab = tab;
	parse_cmd(v);
	i = -1;
	while (tab[++i])
	{
	//	printf("i:%d = %s\n", i, tab[i]);
		free(tab[i]);
	}
	free(tab);
	return (1);
}
