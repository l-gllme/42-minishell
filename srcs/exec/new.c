/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 11:57:41 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler2(int signum)
{
	if (signum == 3 && g_shell.in_exec == 1)
	{
		write (2, "lol\n", 4);
		g_shell.retour = 131;
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
	int		i;

	i = 0;
	dev = open("/dev/urandom", O_RDONLY);
	if (dev == -1)
		return (ft_custom_error("open error in create_tmp_file()\n", 0, NULL));
	read(dev, random, 10);
	close(dev);
	random[10] = 0;
	while (random[i])
	{
		if (random[i] == '/')
			random[i] = 123;
		i++;
	}
	close(dev);
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
			signal(SIGQUIT, handler2);
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

int	ft_exec_builtin(t_g *v, t_l *tmp)
{
	int	fd;

	if (tmp->name_out)
	{
		if (tmp->append)
			fd = open(tmp->name_out, O_WRONLY | O_APPEND, 0644);	
		else
			fd = open(tmp->name_out, O_WRONLY | O_TRUNC, 0644);	
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	ft_is_builtin(tmp->exec, v, 1, tmp);
	if (tmp->name_out)
		dup2(STDIN_FILENO, STDOUT_FILENO);
	return (1);
}

int	ft_exec_cmd_no_redirect(t_g *v, t_l *tmp, char *str, int pipe_fd[2], int fd_tmp)
{
	int	frk;
	int	fd;
	char	**toto;
	char	*srt;
	int	value;

	value = 0;
	//g_shell.retour = 89;
	g_shell.in_exec = 1;
	frk = fork();
	if (frk == 0)
	{
		signal(SIGQUIT, handler);
		if (tmp->arg != NULL && !ft_is_builtin(tmp->exec, v, 0, tmp))
		{
			srt = ft_strjoin(tmp->exec, " ");
			srt = ft_strjoin_gnl(srt, tmp->arg);
			toto = ft_split(srt, ' ');
			free(srt);
		}
		else if (!ft_is_builtin(tmp->exec, v, 0, tmp))
			toto = ft_split(tmp->exec, ' ');
		if (tmp->name_in)
		{
			fd = open(tmp->name_in, 0, 0644);	
			if (fd == -1 && access(tmp->name_in, X_OK))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->name_in, 2);
				ft_putstr_fd(" :Permission denied\n", 2);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (v->dup_type != 1)
				close(fd_tmp);
		}
		else if (v->dup_type != 1)
		{
			dup2(fd_tmp, STDIN_FILENO);
		}
		if (tmp->name_out)
		{
			if (tmp->append)
				fd = open(tmp->name_out, O_WRONLY | O_APPEND, 0644);	
			else
				fd = open(tmp->name_out, O_WRONLY | O_TRUNC, 0644);	
			dup2(fd, STDOUT_FILENO);
			close(fd);
			//close(pipe_fd[1]);
		}
		else if (tmp->next)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
		}
		if (ft_is_builtin(tmp->exec, v, 1, tmp))
		{
			ft_lstclear(&v->list, &free);
			ft_free(v);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(g_shell.retour);
		}
		close(pipe_fd[1]);
		if (str != NULL)
			execve(str, toto, v->new_env);
		close(pipe_fd[1]);
		if (fd_tmp)
			close(fd_tmp);
		ft_lstclear(&v->list, &free);
		ft_free(v);
		free_char_tab(toto);
		g_shell.retour = 127;
		exit(value);
	}
	if (v->dup_type != 1)
		close(fd_tmp);
	close(pipe_fd[1]);
	free(v->wagon);
	if (WTERMSIG(value) == 3)
	{
		printf ("Quit (core dumped)\n");
		g_shell.retour = 131;
	}
	//g_shell.retour = WEXITSTATUS(value);
	return (1);
}

int	ft_exec_one_cmd(t_g *v, char *str, t_l *tmp)
{
	int		frk;
	char	**toto;
	char	*srt;
	int		value;
	int	fd;

	value = 0;
	g_shell.in_exec = 1;
	if (v->l->arg != NULL)
	{
		srt = ft_strjoin(v->l->exec, " ");
		srt = ft_strjoin_gnl(srt, v->l->arg);
		toto = ft_split(srt, ' ');
		free(srt);
	}
	else
		toto = ft_split(v->l->exec, ' ');
	frk = fork();
	if (frk == 0)
	{
		signal(SIGQUIT, handler);
		if (tmp->name_in)
		{
			fd = open(tmp->name_in, 0, 0644);	
			if (fd == -1 && access(tmp->name_in, X_OK))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->name_in, 2);
				ft_putstr_fd(" :Permission denied\n", 2);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
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
		if (str != NULL)
			execve(str, toto, v->new_env);
		ft_lstclear(&v->list, &free);
		ft_free(v);
		free_char_tab(toto);
		exit(127);
	}
	else
		waitpid(frk, &value, 0);
	if (WTERMSIG(value) == 3)
	{
		printf ("Quit (core dumped)\n");
		g_shell.retour = 131;
	}
	free_char_tab(toto);
	g_shell.retour = WEXITSTATUS(value);
	return (WEXITSTATUS(value));
}

int	ft_exec_cmd_lol(t_g *v, t_l *tmp, int choice, int pipe_fd[2], int fd_tmp)
{
	char	*str;
	int		value;

	str = NULL;
	value = 0;
	if (ft_is_builtin(tmp->exec, v, 0, tmp))
	{
		ft_exec_cmd_no_redirect(v, tmp, tmp->exec, pipe_fd, fd_tmp);
		return (1);
	}
	else
	{
		if (open(tmp->exec, O_DIRECTORY) != -1)
		{
			g_shell.retour = 126;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->exec, 2);
			ft_custom_error(": Is a directory\n", 0, NULL);
		}
		if (ft_recup_content("PATH", v) == NULL && access(tmp->exec, X_OK) != 0)
		{
			g_shell.retour = 127;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->exec, 2);
			ft_custom_error(": command not found\n", 0, NULL);
		}
		else
			str = try_access(tmp->exec, v);
		if (str == NULL && g_shell.retour != 127)
		{
			g_shell.retour = 127;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->exec, 2);
			ft_custom_error(": command not found\n", 0, NULL);
		}
		if (choice)
			ft_exec_one_cmd(v, str, tmp);
		else
			ft_exec_cmd_no_redirect(v, tmp, str, pipe_fd, fd_tmp);
		free(str);
	}
	return (1);
}

char	**ft_regroup_env(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->list;
	if (v->env[0])
		tmp = tmp->next;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (tmp->next)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	recup[i] = ft_strdup(tmp->line);
	recup[i + 1] = 0;
	return (recup);
}

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;
	int	pipe_fd[2];
	int	fd_tmp;

	g_shell.retour = 0;
	g_shell.in_exec = 0;
	tmp = l;
	v->dup_type = 0;
	fd_tmp = 0;
	v->new_env = ft_regroup_env(v);
	while (tmp)
	{
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
		v->dup_type++;
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 1);
		if (tmp->out_tab != NULL)
			ft_exec_out(v, tmp);
		if (tmp->exec != NULL)
		{
			if (l->next == NULL && ft_is_builtin(l->exec, v, 0, tmp))
				ft_exec_builtin(v, tmp);
			else if (v->nb_cmd == 1)
				ft_exec_cmd_lol(v, tmp, 1, pipe_fd, 0);
			else
			{

				if (v->dup_type != 1)
					fd_tmp = pipe_fd[0];
				if (tmp->next != NULL)
					pipe(pipe_fd);
				ft_exec_cmd_lol(v, tmp, 0, pipe_fd, fd_tmp);
			}
		}
		if (tmp->name_in != NULL)
		{
			if (tmp->in_tab[ft_tablen(tmp->in_tab) - 2][1] != 0)
				unlink(tmp->name_in);
		}
		tmp = tmp->next;
	}
	if (l->next == NULL)
	{
		return (1);
	}
	while (v->nb_cmd)
	{
		wait (NULL);
		v->nb_cmd--;
	}
	if (fd_tmp)
		close(fd_tmp);
	return (1);
}
