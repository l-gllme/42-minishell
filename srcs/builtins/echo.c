/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:28 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/06 17:29:11 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_options(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		ft_suppr_dq_sq(tab[i]);
		j = 0;
		if (tab[i][j] && tab[i][j++] == '-' && tab[i][j] == 'n')
		{
			while (tab[i][j] == 'n')
				j++;
			if (tab[i][j] && tab[i][j] != 'n')
				return (1);
		}
		else
			return (i);
		i++;
	}
	return (i);

}


void	ft_echo(char *str)
{
	int	i;
	int	j;
	char	**tab;

	if (!str)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	tab = ft_supersplit(str, ' ');
	i = ft_check_options(tab);
	j = i;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		i++;
		if (tab[i])
			ft_putchar_fd(' ', 1);
	}
	if (!j)
		ft_putchar_fd('\n', 1);
}
