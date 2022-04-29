/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:39:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/28 12:43:08 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin(char *str, t_g *v, int choice)
{
	if (ft_strcmp(str, "echo") == 0)
	{
		if (choice)
			ft_echo(v->l->arg);
		else
			v->nb_built++;
		g_retour = 0;
		return (1);
	}
	if (ft_strcmp(str, "pwd") == 0)
	{
		if (choice)
			ft_pwd();
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "cd") == 0)
	{
		if (choice)
		{
			if (!ft_cd(v->l->arg, v))
				g_retour = 1;
		}
		else
			v->nb_built++;
		return (2);
	}
	if (ft_strcmp(str, "env") == 0)
	{
		if (choice)
			ft_env(v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "unset") == 0)
	{
		if (choice)
			ft_unset(v->l->arg, v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "export") == 0)
	{
		if (choice)
			ft_export(v->l->arg, v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "exit") == 0)
	{
		if (choice)
			ft_exit(v->l->arg);
		else
			v->nb_built++;
		return (1);
	}
	return (0);
}
