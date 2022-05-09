/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:33:21 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 17:39:10 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_mega_atoi(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	ft_exit_error_1(char **split, char *line, char *tmp, t_g *v)
{
	(void)line;
	if (!tmp)
	{
		printf("Minishell: exit: %s: numeric argument required\n", split[0]);
		printf("Bye! 👋\n");
		ft_lstclear(&v->list, &free);
		ft_free(v);
		free_char_tab(split);
		exit(2);
	}
	else
	{
		printf("exit\nMinishell: exit: too many arguments\n");
		g_shell.retour = 1;
		free_char_tab(split);
		free(tmp);
	}
}

void	ft_error_exit_2(char **split, t_g *v, char *tmp)
{
	(void)tmp;
	printf("Bye! 👋\n");
	printf("Minishell: exit: %s: numeric argument required\n", split[0]);
	g_shell.retour = 1;
	ft_lstclear(&v->list, &free);
	free_char_tab(split);
	ft_free(v);
	if (tmp)
		free(tmp);
	exit (2);
}

static void	ft_exit_2(char **split, int valeur, char *tmp, t_g *v)
{
	printf("Bye! 👋\n");
	free(tmp);
	free_char_tab(split);
	ft_lstclear(&v->list, &free);
	ft_free(v);
	exit(valeur);
}

void	ft_exit(char *line, t_g *v)
{
	long long	valeur;
	char		*tmp;
	char		**split;
	int			i;

	if (!line)
	{
		ft_lstclear(&v->list, &free);
		ft_free(v);
		free(line);
		exit(g_shell.retour);
	}
	split = ft_split(line, ' ');
	i = -1;
	while (split[0][++i])
		if (ft_isalpha(split[0][i]))
			ft_exit_error_1(split, line, NULL, v);
	valeur = ft_mega_atoi(line);
	tmp = ft_itoa(valeur);
	if (split[1] != NULL)
		ft_exit_error_1(split, line, tmp, v);
	else if (ft_strcmp(line, tmp))
		ft_error_exit_2(split, v, tmp);
	else
		ft_exit_2(split, valeur, tmp, v);
}
