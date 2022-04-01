/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:35:00 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/01 13:58:15 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == 0)
		ft_putstr_fd("Malloc error\n", 2);
	if (error == 1)
		ft_putstr_fd("Env/path not found\n", 2);
	if (error == 2)
		ft_putstr_fd("Incorect number of arguments\n\n", 2);
	exit(0);
}

void	ft_free(t_g *v)
{
	if (v)
	{
		if (v->cmd != NULL)
		{
			free_char_tab(v->cmd);
			v->cmd = NULL;
		}
		if (v->tab != NULL)
		{
			free_char_tab(v->tab);
			v->tab = NULL;
		}
		if (v->l.in_tab != NULL)
		{
			free_char_tab(v->l.in_tab);
			v->l.in_tab = NULL;
		}
		if (v->l.out_tab != NULL)
		{
			free_char_tab(v->l.out_tab);
			v->l.out_tab = NULL;
		}
		if (v->l.exec != NULL)
		{
			free(v->l.exec);
			v->l.exec = NULL;
		}
		if (v->l.arg != NULL)
		{
			free(v->l.arg);
			v->l.arg = NULL;
		}

		free(v);
	}
}

int	ft_custom_error(char *str, int ret, t_g *v)
{
	ft_free(v);
	if (str)
		ft_putstr_fd(str, 2);
	return (ret);
}
