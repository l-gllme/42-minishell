/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/30 17:52:00 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler2(int signum)
{
	if (signum == 3)
	{
		g_shell.retour = 131;
		printf("A faire...");
	}
	if (signum == 2)
	{
		g_shell.retour = 130;
		free(g_shell.test);
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
	
	i = g_shell.retour;
	int	frk = fork();
	if (frk == 0)
	{
		g_shell.test = ft_strdup(limiter);
		ft_lstclear(&v->list, &free);
		ft_free(v);
		while (1)
		{
			signal(SIGINT, handler2);
			str = readline("> ");
			g_shell.str = str;
			if (str == NULL)
			{
				printf("\n");
				printf ("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')", g_shell.test);
				free(g_shell.test);
				g_shell.retour = i;
				exit(0);
			}
			else if (str[0] != 0 && str && ft_strcmp(str, g_shell.test) == 0)
			{
				free(str);
				free(g_shell.test);
				g_shell.retour = i;
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
		if (WTERMSIG(value) == 0)
		{
			g_shell.retour = 130;
			printf("\n");
		}
		else
			g_shell.retour = i;
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
		if (g_shell.retour == 130)
			return (0);
		if (tmp->in_tab != NULL && g_shell.retour != 130)
			ft_exec_in(v, tmp, 0);
		tmp = tmp->next;
	}
	/*tmp = l;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 1);
		if (tmp->out_tab != NULL)
			ft_exec_out(v, tmp);
		//if (tmp->exec != NULL)
		//	ft_exec_cmd(v, tmp);
		tmp = tmp->next;
	}*/
	return (1);
}
