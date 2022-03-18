/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/17 17:25:33 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_cd(char *arg)
{
	char	*str;
	int		i;

	i = 0;
	if (!arg[0])
	{
		str = getenv("HOME");
		if (chdir(str) == -1)
			ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
	}
	if (arg[0] == '~')
	{
		str = getenv("HOME");
		if (ft_strlen(arg) == 1)
		{
		}
		else if (ft_strlen(arg) == 2)
		{
			if (arg[1] == '/')
			{
				if (chdir(str) == -1)
					ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
			}
			else
			{
				str = ft_strjoin(str, arg);
				i = 1;
			}
		}
		else
		{
			str = ft_strjoin(str, arg + 1);
			i = 1;
		}
		if (chdir(str) == -1)
			ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
		if (i)
			free(str);
	}
	else 
		if (chdir(arg) == -1)
			ft_putstr_fd("MiniShell: cd: no such file or directory\n", 2);
}
