/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/02 13:02:13 by jtaravel         ###   ########.fr       */
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
		exit(2);
	}
	else
		return ;
}

int	create_tmp_file(t_l *tmp)
{
	int		dev;
	char	random[11];

	dev = open("/dev/urandom", O_RDONLY);
	if (dev == -1)
		return (ft_custom_error("open error in create_tmp_file()\n", 0, NULL));
	read(dev, random, 10);
	close(dev);
	random[10] = 0;
	tmp->name_in = ft_strjoin(".tmp_file", random);
	if (!tmp->name_in)
		return (ft_custom_error("strjoin error in create_tmp_file()\n",
				0, NULL));
	return (1);
}



int	ft_here_doc_no_cmd(char *limiter, t_g *v, t_l *tmp)
{
	char	*str;
	int	i;
	int	value = 0;
	
	i = g_shell.retour;
	if (v->dup_type == 10)
	{
		if (!create_tmp_file(tmp))
			return (0);
		if (v->dup_type == 10)
			tmp->in = open(tmp->name_in, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
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
			if (v->dup_type == 10)
			{
				ft_putstr_fd(str, tmp->in);
				ft_putstr_fd("\n", tmp->in);
			}
			g_shell.str = str;
			if (str == NULL)
			{
				printf("\n");
				printf ("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", g_shell.test);
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
		if (v->dup_type == 10)
			v->dup_type = 0;
		close(tmp->in);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(frk, &value, 0);
		if (WEXITSTATUS(value) == 2)
		{
			printf ("lol\n");
			if (tmp->name_in)
			{
				printf ("salut\n");
				unlink(tmp->name_in);
			}
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

	g_shell.retour = 0;
	tmp = l;
	while (tmp)
	{
		tmp->in = -1;
		tmp->out = -1;
		tmp->name_in = NULL;
		tmp->name_out = NULL;
		if (tmp->in_tab != NULL && g_shell.retour != 130)
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
		if (tmp->exec != NULL)
			ft_exec_cmd_test(tmp, v);
		tmp = tmp->next;
	}
	return (1);
}
