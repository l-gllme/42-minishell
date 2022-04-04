/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/04 17:26:49 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_cd(char *arg)
{
	char	*str;
	int		i;

	i = 0;
	if (!arg)
	{
		ft_putstr_fd("toto", 2);
		return ;
	}
	if (!arg[0])
	{
		str = getenv("HOME");
		if (chdir(str) == -1)
			ft_putstr_fd("miniShell: cd: no such file or directory\n", 2);
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
					ft_putstr_fd("miniShell: cd: no such file or directory\n", 2);
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
			ft_putstr_fd("miniShell: cd: no such file or directory\n", 2);
		if (i)
			free(str);
	}
	else 
	{
		if (chdir(arg) == -1)
		{
			arg = ft_strjoin("/", arg);
			str = ft_strjoin(getcwd(NULL, 0), arg);
		}
		if (chdir(str) == -1)
		{
			ft_putstr_fd("miniShell: cd: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
}
