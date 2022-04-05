/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/05 14:35:04 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	error_cd(char *arg)
{
	
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

int	ft_cd(char *arg)
{
	char	*str;
	int		i;

	ft_putstr_fd(arg, 2);
	if (!arg)
	{
		str = getenv("HOME");
		if (chdir(str) == -1)
			return (error_cd(arg));
	}
	i = -1;
	while (arg[++i])
		;
	i--;
	arg[i] = 0;
	i = 0;
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
					return (error_cd(arg));
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
				return (error_cd(arg));
		if (i)
			free(str);
	}
	else 
	{
		if (chdir(arg) == -1)
			return (error_cd(arg));
	}
	return (1);
}
