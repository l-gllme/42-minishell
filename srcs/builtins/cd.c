/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/16 17:58:13 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_cd(char *arg)
{
	char	*str;
	int		i;

	i = 1;
	if (arg[0] == '~')
	{
		str = getenv("HOME");
		if (chdir(str) == -1)
			ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
		free(str);
		if (arg[1] == '/')
			i++;
		if (arg[i])
		{
			if (chdir(str + i) == -1)
				ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
		}
	}
	else 
		if (chdir(arg) == -1)
			ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
}
