/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:28 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/16 17:57:31 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_echo(char *arg)
{
	int	i;
	int	j;
	char	**str;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
			j++;
		i++;
	}
	if (j % 2 != 0)
	{
		printf("Invalid syntax\n");
		return ;
	}
	str = ft_split(arg, ' ');
	if (str[1] == 0 && ft_strlen(str[0]) == 4)
	{
		write(1, "\n", 1);
		return ;
	}	
	if (ft_strncmp(str[1], "-n", 2) == 0 && str[2] == 0)
		return ;
	i = 1;
	while (str[i] && ft_strncmp(str[1], "-n", 2) != 0)
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != '"' || str[i][j] != ''')
				printf("%c", str[i][j]);
			j++;
		}
		if (str[i + 1] != 0)
			printf(" ");
		i++;
	}
	if(ft_strncmp(str[1], "-n", 2) != 0)
		printf("\n");
	i = 2;
	while  (str[i] && ft_strncmp(str[1], "-n", 2) == 0)
	{
		j = 0;	
		while (str[i][j])
		{
			if (str[i][j] != '"' || str[i][j] != ''')
				printf("%c", str[i][j]);
			j++;
		}
		if (str[i + 1] != 0)
			printf(" ");
		i++;
	}

}

