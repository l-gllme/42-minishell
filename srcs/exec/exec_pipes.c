/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:54:41 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/28 12:55:56 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	c_est_hess_gow(t_g *v, char *str)
{
	char **toto;
	char *srt;
	int	value;

	value = 0;
	if (v->l->arg != NULL)
	{
		srt = ft_strjoin(v->l->exec, " ");
		srt = ft_strjoin_gnl(srt, v->l->arg);
		toto = ft_split(srt, ' ');
		free(srt);
	}
	else
		toto = ft_split(v->l->exec, ' ');
	execve(str, toto, v->new_env);
	free(str);
	free_char_tab(toto);
	return (value);
}

int	exec_command_pipe(t_g *v)
{
	char	*str;
	int		value;

	value = 0;
	if (ft_recup_content("PATH", v) == NULL && access(v->l->exec, X_OK) != 0)
	{
		value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(v->l->exec, 2);
		ft_custom_error(": command not found\n", 0, v);
		return (value);
	}
	str = try_access(v->l->exec, v);
	if (str == NULL && !ft_is_builtin(v->l->exec, v, 0))
	{
		value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(v->l->exec, 2);
		ft_custom_error(": command not found\n", 0, v);
		return (value);
	}
	value = c_est_hess_gow(v, str);
	return (value);
}

int	pipe_exec(t_g *v)
{
	if (v->l->exec != NULL)
	{
		if (v->l->in_tab != NULL)
			exec_in_dup(v, v->l->in_tab, 0);
		if (v->l->out_tab != NULL)
			exec_out_dup(v, v->l->out_tab);
		v->nb_built = 0;
		//ft_is_builtin(v->l->exec, v, 0);
		if (v->nb_built != 0)
			ft_is_builtin(v->l->exec, v, 1);
		exec_command_pipe(v);
	}
	else
	{
		if (v->l->in_tab != NULL)
			exec_in(v, v->l->in_tab);
		if (v->l->out_tab != NULL)
			exec_out(v, v->l->out_tab);
	}
	return (1);	
}

static void	exec_first(int	*fd, t_g *v)
{
	int		frk;

	frk = fork();
	if (frk == -1)
		return ;
	if (frk == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		pipe_exec(v);
		//execve(try_access(v->l->exec, v), &v->l->exec, v->env);
	}
}

static void	exec_second(int	*fd, t_g *v)
{
	int		frk;

	frk = fork();
	if (frk == -1)
		return ;
	if (frk == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		pipe_exec(v);
	}
}

int	ft_exec_pipes(t_g *v)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (0);
	exec_first(fd, v);
	v->l = v->l->next;
	exec_second(fd, v);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (1);
}
