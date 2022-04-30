/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:33:21 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/30 13:30:47 by jtaravel         ###   ########.fr       */
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

void	ft_exit(char *line)
{
	long long	valeur;
	char	*tmp;
	char	**split;
	int	i;

	i = 0;
	if (!line)
	{
		ft_putstr_fd("Bye! 👋\n", 1);
		free(line);
		exit (g.retour);
	}
	split = ft_split(line, ' ');
	line[ft_strlen(line) - 1] = 0;
	while (split[0][i])
	{
		if (ft_isalpha(split[0][i]))
		{
			printf("Minishell: exit: %s: numeric argument required\n", split[0]);
			valeur = 2;
			free(line);
			ft_putstr_fd("Bye! 👋\n", 1);
			exit(valeur);
		}
		i++;
	}		
	valeur = ft_mega_atoi(line);
	tmp = ft_itoa(valeur);
	if (ft_strcmp(line, tmp))
	{
		printf("Minishell: exit: %s: numeric argument required\n", split[0]);
		g.retour = 1;
		free(line);
		return ;
	}
	else if (split[1] != NULL)
	{
		printf("exit\nMinishell: exit: too many arguments\n");
		g.retour = 2;
		free(line);
		free (tmp);
		return ;
	}
	ft_putstr_fd("Bye! 👋\n", 1);
	free(line);
	free (tmp);
	free_char_tab(split);
	exit(valeur);
}
