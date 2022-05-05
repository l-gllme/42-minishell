/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:33:21 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 12:39:51 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_mega_atoi(char *str)
{
	int	i;
	long long	res;
	int	sign;

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

void	ft_exit_error_1(char *split, char *line)
{
	int valeur;

	printf("Minishell: exit: %s: numeric argument required\n", split);
	valeur = 2;
	free(line);
	printf("Bye! 👋\n");
	exit(valeur);
}

void	ft_exit(char *line)
{
	long long	valeur;
	char	*tmp;
	char	**split;
	int	i;

	i = 0;
	if (!line)
	{
		free(line);
		exit(g_shell.retour);
	}
	split = ft_split(line, ' ');
	line[ft_strlen(line) - 1] = 0;
	while (split[0][i])
	{
		if (ft_isalpha(split[0][i]))
		{
			ft_exit_error_1(split[0], line);
		}
		i++;
	}		
	valeur = ft_mega_atoi(line);
	tmp = ft_itoa(valeur);
	if (ft_strcmp(line, tmp))
	{
		printf("Bye! 👋\n");
		printf("Minishell: exit: %s: numeric argument required\n", split[0]);
		g_shell.retour = 1;
		exit (0);
	}
	else if (split[1] != NULL)
	{
		printf("exit\nMinishell: exit: too many arguments\n");
		g_shell.retour = 2;
		free(line);
		free (tmp);
		return ;
	}
	printf("Bye! 👋\n");
	free (tmp);
	free_char_tab(split);
	exit(valeur);
}
