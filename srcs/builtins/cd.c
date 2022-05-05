/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:04:06 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 13:48:13 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	error_cd(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

int	perm_cd(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (0);
}

static int	cut_cd_error_chdir(char *str, char *arg, int i)
{
	if (access(str, F_OK))
	{
		if (i)
			free(str);
		return (error_cd(arg));
	}
	else
	{
		if (i)
			free(str);
		return (perm_cd(arg));
	}
}

static int	cut_cd_tild_2(char *arg, int i, t_g *v)
{
	char	*str;

	str = ft_recup_content("HOME", v);
	if (str == NULL)
		return (ft_custom_error("minishell: cd: HOME not set\n", 0, NULL));
	if (ft_strlen(arg) == 2)
	{
		if (!cut_cd_just_tild(arg, str, &i))
			return (0);
		if (i == 10)
			return (1);
	}
	else
	{
		str = ft_strjoin(str + 1, arg + 1);
		i = 1;
	}
	if (chdir(str) == -1)
		return (cut_cd_error_chdir(str, arg, i));
	if (i)
		free(str);
	return (1);
}

int	ft_cd(char *arg, t_g *v)
{
	if (arg == NULL)
		return (cut_cd_no_arg_or_multiple(arg, v, 0));
	if (!cut_cd_no_arg_or_multiple(arg, v, 1))
		return (0);
	ft_suppr_dq_sq(arg);
	if (arg[0] == '~')
		return (cut_cd_tild_2(arg, 0, v));
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
