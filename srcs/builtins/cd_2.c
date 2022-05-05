/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:44:19 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 13:45:30 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	cut_cd_no_arg_or_multiple(char *arg, t_g *v, int choice)
{
	char	**tab;
	char	*str;

	if (!choice)
	{
		str = ft_recup_content("HOME", v);
		if (str == NULL)
			return (ft_custom_error("minishell: cd: HOME not set\n", 0, NULL));
		if (chdir(str + 1) == -1)
			return (error_cd(str + 1));
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
	return (1);
}

int	cut_cd_just_tild(char *arg, char *str, int *i)
{
	if (arg[1] == '/')
	{
		if (chdir(str + 1) == -1)
		{
			if (access(str + 1, F_OK))
				return (error_cd(arg));
			else
				return (perm_cd(arg));
		}
		else
			return (*i = 10);
	}
	else
	{
		ft_putstr_fd("minishell: no such user or named directory: ", 2);
		ft_putstr_fd(arg + 1, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}
