/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/02 17:59:11 by jtaravel         ###   ########.fr       */
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
	int	c;
	int	fd;
	
	fd = 0;
	i = g_shell.retour;
	ft_suppr_dq_sq(limiter);
	if (v->dup_type == 10)
	{
		if (!create_tmp_file(tmp))
			return (0);
		if (v->dup_type == 10)
			tmp->in = open(tmp->name_in, O_CREAT | O_WRONLY | O_APPEND, 0644);
		fd = tmp->in;
	}
	int	frk = fork();
	c = v->dup_type;
	if (frk == 0)
	{
		g_shell.test = ft_strdup(limiter);
		ft_lstclear(&v->list, &free);
		ft_free(v);
		while (1)
		{
			signal(SIGINT, handler2);
			str = readline("> ");
			if (c == 10 && str && str[0] != 0 && ft_strcmp(str, g_shell.test) != 0)
			{
				ft_putstr_fd(str, fd);
				ft_putstr_fd("\n", fd);
			}
			else if (fd != 0)
				close(fd);
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
		if (c == 10)
			c = 0;
		if (fd != 0)
			close(fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(frk, &value, 0);
		if (WEXITSTATUS(value) == 2)
		{
			if (tmp->name_in)
			{
				close(tmp->in);
				unlink(tmp->name_in);
			}
			g_shell.retour = 130;
			printf("\n");
		}
		else
			g_shell.retour = i;
	}
	if (tmp->in != -1)
		close(tmp->in);
	return (1);
}

static int	create_tmp_file_exec(t_g *v)
{
	int		dev;
	char	random[11];

	dev = open("/dev/urandom", O_RDONLY);
	if (dev == -1)
		return (ft_custom_error("open error in create_tmp_file()\n", 0, NULL));
	read(dev, random, 10);
	close(dev);
	random[10] = 0;
	v->urandom = ft_strjoin(".tmp_file", random);
	if (!v->urandom)
		return (ft_custom_error("strjoin error in create_tmp_file()\n",
				0, NULL));
	return (1);
}


int	ft_exec_cmd_no_redirect(t_g *v, t_l *tmp)
{
	int	frk;
	int	pipe_fd[2];
	int	fd;
	int	value;
	char	**toto;
	char	*srt;
	char	*str;

	value = 0;
	str = try_access(tmp->exec, v);
	if (v->urandom != NULL)
		v->wagon = ft_strdup(v->urandom);
	if (tmp->next && !tmp->name_out)
	{
		create_tmp_file_exec(v);
		v->fd_in = open(v->urandom, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(v->fd_in);
	}
	pipe(pipe_fd);
	frk = fork();
	if (frk == 0)
	{
		if (tmp->arg != NULL)
		{
			srt = ft_strjoin(tmp->exec, " ");
			srt = ft_strjoin_gnl(srt, tmp->arg);
			toto = ft_split(srt, ' ');
			free(srt);
		}
		else
			toto = ft_split(tmp->exec, ' ');
		if (tmp->name_in)
		{
			fd = open(tmp->name_in, 0, 0644);	
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (v->wagon != NULL)
		{
			fd = open(v->wagon, 0, 0644);	
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(v->wagon);
		}
		else if (tmp->next)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
		}
		if (tmp->name_out)
		{
			if (tmp->append)
				fd = open(tmp->name_out, O_WRONLY | O_APPEND, 0644);	
			else
				fd = open(tmp->name_out, O_WRONLY | O_TRUNC, 0644);	
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (tmp->next)
		{
			v->fd_in = open(v->urandom, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(v->fd_in, STDOUT_FILENO);
			close(v->fd_in);
		}
		if (v->wagon)
			unlink(v->wagon);
		execve(str, toto, v->new_env);
	}
	else
	{
		waitpid(frk, &value, 0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait (NULL);
	return (WEXITSTATUS(value));
}

int	ft_exec_cmd_lol(t_g *v, t_l *tmp)
{
	ft_exec_cmd_no_redirect(v, tmp);
	return (1);
}

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;

	g_shell.retour = 0;
	tmp = l;
	while (tmp)
	{
		v->wagon = NULL;
		v->urandom = NULL;
		tmp->in = -1;
		tmp->out = -1;
		tmp->name_in = NULL;
		tmp->name_out = NULL;
		v->dup_type = 0;
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
			ft_exec_cmd_lol(v, tmp);
		if (tmp->name_in != NULL)
		{
			if (tmp->in_tab[ft_tablen(tmp->in_tab) - 2][1] != 0)
				unlink(tmp->name_in);
		}
		tmp = tmp->next;
	}
	return (1);
}
