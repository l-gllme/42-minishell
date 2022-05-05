/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:39:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 13:48:41 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_builtin_3(char *str, t_g *v, int choice, t_l *tmp)
{
	if (ft_strcmp(str, "unset") == 0)
	{
		if (choice)
			ft_unset(tmp->arg, v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "export") == 0)
	{
		if (choice)
			ft_export(tmp->arg, v);
		else
			v->nb_built++;
		return (1);
	}
	if (ft_strcmp(str, "exit") == 0)
	{
		if (choice)
			ft_exit(tmp->arg);
		else
			v->nb_built++;
		return (1);
	}
	return (0);
}

int	ft_is_builtin_2(char *str, t_g *v, int choice, t_l *tmp)
{
	int	value;

	if (ft_strcmp(str, "cd") == 0)
	{
		if (choice)
		{
			if (!ft_cd(tmp->arg, v))
				g_shell.retour = 1;
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
	else
		value = ft_is_builtin_3(str, v, choice, tmp);
	return (value);
}

int	ft_is_builtin(char *str, t_g *v, int choice, t_l *tmp)
{
	int	value;

	if (ft_strcmp(str, "echo") == 0)
	{
		if (choice)
			ft_echo(tmp->arg);
		else
			v->nb_built++;
		g_shell.retour = 0;
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
	else
		value = ft_is_builtin_2(str, v, choice, tmp);
	return (value);
}
