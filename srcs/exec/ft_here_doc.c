/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:11:58 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 14:26:17 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_here_doc_2(int fd, int c)
{
	char	*str;

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
		ft_error_str_null();
	else if (str[0] != 0 && str && ft_strcmp(str, g_shell.test) == 0)
		ft_error_limiter(str);
	free(str);
}

void	ft_here_doc_else_fork(int frk, int value, t_l *tmp, int i)
{
	signal(SIGINT, SIG_IGN);
	waitpid(frk, &value, 0);
	if (WEXITSTATUS(value) == 2)
		ft_value_is_2(tmp);
	else
		g_shell.retour = i;
}

int	ft_init_fd(t_l *tmp, int fd, t_g *v)
{
	if (!create_tmp_file(tmp))
		return (0);
	if (v->dup_type == 10)
		tmp->in = open(tmp->name_in, O_CREAT | O_WRONLY | O_APPEND, 0644);
	fd = tmp->in;
	return (fd);
}

void	ft_here_doc_no_cmd_2(char *limiter, t_g *v, int fd, int c)
{
	g_shell.test = ft_strdup(limiter);
	ft_lstclear(&v->list, &free);
	ft_free(v);
	while (1)
		ft_here_doc_2(fd, c);
	if (c == 10)
		c = 0;
	if (fd != 0)
		close(fd);
	exit(0);
}

int	ft_here_doc_no_cmd(char *limiter, t_g *v, t_l *tmp, int value)
{
	int	i;
	int	c;
	int	fd;
	int	frk;

	fd = 0;
	i = g_shell.retour;
	ft_suppr_dq_sq(limiter);
	if (v->dup_type == 10)
		fd = ft_init_fd(tmp, fd, v);
	frk = fork();
	c = v->dup_type;
	if (frk == 0)
		ft_here_doc_no_cmd_2(limiter, v, fd, c);
	else
		ft_here_doc_else_fork(frk, value, tmp, i);
	if (tmp->in != -1)
		close(tmp->in);
	return (1);
}
