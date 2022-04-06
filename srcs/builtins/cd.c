/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/06 16:37:23 by lguillau         ###   ########.fr       */
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

static int	perm_cd(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (0);
}
 
int	ft_cd(char *arg)
{
	char	*str;
	int		i;
	char	**tab;

	if (arg == NULL)
	{
		str = getenv("HOME");
		if (str == NULL)
			return (ft_custom_error("minishell: cd: HOME not set\n", 0, NULL));
		if (chdir(str) == -1)
			return (ft_custom_error("minishell: chdir error in ft_cd()\n", 0, NULL));
		return (1);
	}
	tab = ft_supersplit(arg, ' ');
	if (!tab)
		return (ft_custom_error("malloc error in ft_cd()\n", 0, NULL));
	if (tab[1] != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		free_char_tab(tab);
		return (ft_custom_error("too many arguments\n", 0, NULL));
	}
	free_char_tab(tab);
	ft_suppr_dq_sq(arg);
	i = -1;
	while (arg[++i])
		;
	i--;
	arg[i] = 0;
	i = 0;
	if (arg[0] == '~')
	{
		str = getenv("HOME");
		if (ft_strlen(arg) == 2)
		{
			if (arg[1] == '/')
			{
				if (chdir(str) == -1)
				{
					if (access(str, F_OK))
						return (error_cd(arg));
					else
						return (perm_cd(arg));
				}
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
		{
			if (access(str, F_OK))
				return (error_cd(arg));
			else
				return (perm_cd(arg));
		}
		if (i)
			free(str);
	}
	else 
	{
		if (chdir(arg) == -1)
		{
			if (access(arg, F_OK))
				return (error_cd(arg));
			else
				return (perm_cd(arg));
		}
	}
	return (1);
}
