/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 16:42:22 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_error_exec(t_l *tmp, int choice)
{
	if (choice == 1)
	{
		g_shell.retour = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->exec, 2);
		ft_custom_error(": command not found\n", 0, NULL);
	}
	else if (choice == 0)
	{
		g_shell.retour = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->exec, 2);
		ft_custom_error(": Is a directory\n", 0, NULL);
	}
}

void	ft_exec_cmd_lol_2(t_l *tmp, t_g *v, int choice, int pipe_fd[2])
{
	char	*str;

	str = NULL;
	if (open(tmp->exec, O_DIRECTORY) != -1)
		ft_error_exec(tmp, 0);
	if (ft_recup_content("PATH", v) == NULL && access(tmp->exec, X_OK) != 0)
		ft_error_exec(tmp, 1);
	else
		str = try_access(tmp->exec, v);
	if (str == NULL)// && g_shell.retour != 127)
		ft_error_exec(tmp, 1);
	if (choice)
		ft_exec_one_cmd(v, str, tmp);
	else
		ft_exec_cmd_no_redirect(v, tmp, str, pipe_fd);
	free(str);
}

int	ft_exec_cmd_lol(t_g *v, t_l *tmp, int choice, int pipe_fd[2])
{
	int		value;

	value = 0;
	if (ft_is_builtin(tmp->exec, v, 0, tmp))
	{
		ft_exec_cmd_no_redirect(v, tmp, tmp->exec, pipe_fd);
		return (1);
	}
	else
		ft_exec_cmd_lol_2(tmp, v, choice, pipe_fd);
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

void	ft_exec_3(t_l *l, t_l *tmp, int pipe_fd[2], t_g *v)
{
	if (l->next == NULL && ft_is_builtin(l->exec, v, 0, tmp))
		ft_exec_builtin(v, tmp);
	else if (v->nb_cmd == 1)
		ft_exec_cmd_lol(v, tmp, 1, pipe_fd);
	else
	{
		if (v->dup_type != 1)
			v->fd_tmp = pipe_fd[0];
		if (tmp->next != NULL)
			pipe(pipe_fd);
		ft_exec_cmd_lol(v, tmp, 0, pipe_fd);
	}
}

void	ft_exec_2(t_g *v, t_l *tmp, t_l *l)
{
	int	pipe_fd[2];

	tmp = l;
	v->fd_tmp = 0;
	while (tmp)
	{
		if (tmp->in_tab != NULL)
			ft_exec_in(v, tmp, 1);
		if (tmp->out_tab != NULL && tmp->exec == NULL)
			ft_exec_out(v, tmp);
		if (tmp->exec != NULL)
		{
			v->dup_type++;
			ft_exec_3(l, tmp, pipe_fd, v);
		}
		if (tmp->name_in != NULL)
		{
			if (tmp->in_tab[ft_tablen(tmp->in_tab) - 2][1] != 0)
				unlink(tmp->name_in);
		}
		tmp = tmp->next;
	}
	if (v->fd_tmp)
		close(v->fd_tmp);
}

int	ft_exec(t_g *v, t_l *l)
{
	t_l	*tmp;

	g_shell.retour = 0;
	g_shell.in_exec = 0;
	tmp = l;
	v->dup_type = 0;
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
	ft_exec_2(v, tmp, l);
	while (v->nb_cmd && l->next != NULL)
	{
		wait (NULL);
		v->nb_cmd--;
	}
	return (1);
}
