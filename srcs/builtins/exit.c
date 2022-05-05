/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:33:21 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 13:05:25 by jtaravel         ###   ########.fr       */
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

void	ft_exit_error_1(char *split, char *line, int choice, char *tmp)
{
	if (choice == 0)
	{
		printf("Minishell: exit: %s: numeric argument required\n", split);
		free(line);
		printf("Bye! 👋\n");
		exit(2);
	}
	else if (choice == 1)
	{
		printf("exit\nMinishell: exit: too many arguments\n");
		g_shell.retour = 127;
		free (tmp);
	}
}

void	ft_error_exit_2(char *split)
{
	printf("Bye! 👋\n");
	printf("Minishell: exit: %s: numeric argument required\n", split);
	g_shell.retour = 1;
	exit (2);
}

void	ft_exit_2(char **split, int valeur, char *tmp)
{
	printf("Bye! 👋\n");
	free(tmp);
	free_char_tab(split);
	exit(valeur);
}

void	ft_exit(char *line)
{
	long long	valeur;
	char		*tmp;
	char		**split;
	int			i;

	if (!line)
	{
		free(line);
		exit(g_shell.retour);
	}
	split = ft_split(line, ' ');
	i = -1;
	while (split[0][++i])
		if (ft_isalpha(split[0][i]))
			ft_exit_error_1(split[0], line, 0, NULL);
	valeur = ft_mega_atoi(line);
	tmp = ft_itoa(valeur);
	if (split[1] != NULL)
		ft_exit_error_1(line, tmp, 1, tmp);
	else if (ft_strcmp(line, tmp))
		ft_error_exit_2(split[0]);
	else
		ft_exit_2(split, valeur, tmp);
}
