/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/29 17:45:11 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_here_doc_no_cmd(char *limiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			printf("\n");
			return (1);
		}
		if (str[0] != 0 && str && ft_strcmp(str, limiter) == 0)
		{
			free(str);
			return (1);
		}
		free(str);
	}
	return (1);
}

/*int	ft_exec_cmd_no_redirect(t_g *v, t_l *tmp)
{

}

int	ft_exec_cmd(t_g *v, t_l *tmp)
{
	if (!tmp->in_tab && !tmp->out_tab)
		ft_exec_cmd_no_redirect(v, tmp);
	else
	{
		return (1);
	}
	return (1);
}*/

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;

	tmp = l;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 0);
		tmp = tmp->next;
	}
	tmp = l;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 1);
		if (tmp->out_tab != NULL)
			ft_exec_out(v, tmp);
		//if (tmp->exec != NULL)
		//	ft_exec_cmd(v, tmp);
		tmp = tmp->next;
	}
	return (1);
}
