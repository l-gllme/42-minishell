/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:32:17 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 13:32:58 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_check_not_followed_sign_in_tab(t_g *v, int i)
{
	while (v->l->in_tab[++i])
	{
		if (v->l->in_tab[i + 1] == 0)
		{
			if (v->l->in_tab[i][0] == '<')
			{
				printf("minishell: syntax error near unexpected token");
				return (ft_custom_error("`newline'\n", 0, v));
			}
		}
		else if (v->l->in_tab[i][0] == '<' && v->l->in_tab[i + 1][0] == '<')
		{
			printf("minishell: syntax error near unexpected token");
			return (ft_custom_error("`< or <<'\n", 0, v));
		}
	}
	return (1);
}

int	ft_check_not_followed_sign_out_tab(t_g *v, int i)
{
	while (v->l->out_tab[++i])
	{
		if (v->l->out_tab[i + 1] == 0)
		{
			if (v->l->out_tab[i][0] == '>')
			{
				printf("minishell: syntax error near unexpected token");
				return (ft_custom_error("`newline'\n", 0, v));
			}
		}
		else if (v->l->out_tab[i][0] == '>'
			&& v->l->out_tab[i + 1][0] == '>')
		{
			printf("minishell: syntax error near unexpected token");
			return (ft_custom_error("`> or >>'\n", 0, v));
		}
	}
	return (1);
}

int	check_not_followed_sign(t_g *v)
{
	int	i;

	i = -1;
	if (v->l->in_tab)
	{
		if (!ft_check_not_followed_sign_in_tab(v, i))
			return (0);
	}
	i = -1;
	if (v->l->out_tab)
	{
		if (!ft_check_not_followed_sign_out_tab(v, i))
			return (0);
	}
	return (1);
}
