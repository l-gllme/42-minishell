/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:36:42 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/05 13:05:56 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*try_access(char *cmd)
{
	int		i;
	char	**path;
	char	*s;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
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
	int	frk;
	char	**toto;
	char	*srt;

	if (v->l.arg != NULL)
	{
		srt = ft_strjoin(v->l.exec, " ");
		srt = ft_strjoin_gnl(srt, v->l.arg);
		toto = ft_split(srt, ' ');
	}
	else
		toto = ft_split(v->l.exec, ' ');

	frk = fork();
	if (frk == 0)
	{
		execve(str, toto, v->env);
	}
	else
		wait(NULL);
	return (0);
}

int	ft_is_builtin(char *str, t_g *v)
{
	(void)v;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	{
		ft_echo(v->cmd);
		return (1);
	}
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

int	ft_exec_cmd(t_g *v)
{
	char *str;

	if (ft_is_builtin(ft_suppr_dq_sq(v->l.exec), v))
		return (1);
	str = try_access(v->l.exec);
	if (str == NULL)
	{
		ft_putstr_fd(ft_suppr_dq_sq(v->l.exec), 2);
		ft_custom_error(": command not found\n", 0, v);
		return (0);
	}
	reauckaitte_lygue(v, str);
	return (1);
}
