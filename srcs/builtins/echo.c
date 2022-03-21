/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:28 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/21 16:34:35 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_echo(char *str)
{
	int	i;
	char	**tab;
	int	n;

	n = 0;
	i = 1;
	tab = ft_split(str, ' ');
	if (tab[0][0] == '<')
		i += 2;
	if (tab[i] && ft_strncmp(tab[i], "-n", 2) == 0)
		i++;
	if (i == 2)
		n = 1;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		printf("\n");
}

