/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/30 14:14:32 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler2(int signum)
{
	if (signum == 3)
	{
		g.retour = 131;
		printf("A faire...");
	}
	if (signum == 2)
	{
		g.retour = 130;
		free(g.test);
		exit(0);
	}
	else
		return ;
}

int	ft_here_doc_no_cmd(char *limiter, t_g *v)
{
	char	*str;
	int	i;
	int	value = 0;
	
	i = g.retour;
	int	frk = fork();
	if (frk == 0)
	{
		g.test = ft_strdup(limiter);
		ft_lstclear(&v->list, &free);
		ft_free(v);
		while (1)
		{
			signal(SIGINT, handler2);
			str = readline("> ");
			g.str = str;
			if (str == NULL)
			{
				printf("\n");
				g.retour = i;
				exit(0);
			}
			else if (str[0] != 0 && str && ft_strcmp(str, g.test) == 0)
			{
				free(str);
				free(g.test);
				g.retour = i;
				exit(0);
			}
			free(str);
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(frk, &value, 0);
		if (WTERMSIG(value) == 2)
			printf("\n");

	}
	g.retour = i;
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
