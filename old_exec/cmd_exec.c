/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:36:42 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/27 16:00:35 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*try_access(char *cmd, t_g *v)
{
	int		i;
	char	**path;
	char	*s;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(ft_recup_content("PATH", v) + 1, ':');
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		path[i] = ft_strjoin_gnl(path[i], cmd);
	}
	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
		{
			s = ft_strdup(path[i]);
			free_char_tab(path);
			return (s);
		}
	}
	free_char_tab(path);
	return (NULL);
}

int	reauckaitte_lygue(t_g *v, char *str)
{
	int		frk;
	char	**toto;
	char	*srt;
	int		value;

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
	frk = fork();
	if (frk == 0)
	{
		execve(str, toto, v->new_env);
	}
	else
		waitpid(frk, &value, 0);
	free(str);
	free_char_tab(toto);
	return (WEXITSTATUS(value));
}

int	ft_exec_cmd(t_g *v)
{
	char	*str;
	int		value;

	value = 0;
	if (ft_is_builtin(v->l->exec, v, 1))
		return (1);
	if (ft_recup_content("PATH", v) == NULL && access(v->l->exec, X_OK) != 0)
	{
		value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(v->l->exec, 2);
		ft_custom_error(": command not found\n", 0, v);
		return (value);
	}
	str = try_access(v->l->exec, v);
	if (str == NULL)
	{
		value = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(v->l->exec, 2);
		ft_custom_error(": command not found\n", 0, v);
		return (value);
	}
	value = reauckaitte_lygue(v, str);
	return (value);
}
