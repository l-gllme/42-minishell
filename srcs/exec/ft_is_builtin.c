/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:39:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/12 16:01:27 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin(char *str, t_g *v, int choice)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_echo(v->l.arg);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_pwd();
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_cd(v->l.arg);
		else
			v->nb_built++;
		return (2);
	}
	if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_env(v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_unset(v->l.arg, v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
	{
		if (choice)
			ft_export(v->l.arg, v);
		else
			v->nb_built++;
		return (1);
	}
	return (0);
}
