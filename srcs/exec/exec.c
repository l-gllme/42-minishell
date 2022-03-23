/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:01:01 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/23 13:02:40 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_reverse_chevron(char **str)
{
	int	file;

	file = open(str[1], O_RDONLY);
	if (file == -1)
		printf("error file\n");
	if (dup2(file, STDIN_FILENO) == -1)
	{
		printf("ERROR DUP\n");
		exit(0);
	}
	return (2);
}

int	ft_is_builtin(char *s,  char **cmd)
{
	if (ft_strncmp(s, "echo", ft_strlen(s)) == 0 && ft_strlen(s) == 4)
	{
			printf("s->%s\n", s);
		if (ft_strnstr(cmd[0], s, ft_strlen(cmd[0])))
		{
			ft_echo(ft_strnstr(cmd[0], s, ft_strlen(cmd[0])) + ft_strlen(s));
			close(STDOUT_FILENO);
			dup2(STDIN_FILENO, STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(s, 2);
		}
	}
	return (1);
}

void	ft_exec_outpout(char **cmd)
{
	int	i;
	int	fd;

	i = ft_check_outpout(cmd);
	if (open(cmd[i - 1], O_DIRECTORY) != -1)
	{
		ft_putstr_fd("File is a directory\n", 2);
	}
	fd = open(cmd[i - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_putstr_fd("Permision denied\n", 2);	
	if (!dup2(fd, STDOUT_FILENO))
		ft_putstr_fd("dup2 error\n", 2);	
}

int	ft_check_outpout(char **cmd)
{
	int	i;
	
	i = -1;
	while (cmd[++i])
		;
	if (cmd[i - 2][0] == '>' && cmd[i - 2][1] == 0)
		return (i);
	return (0);
}

void	ft_exec_one_command(t_g *v)
{
	(void)v->file_in;
	ft_putstr_fd("Exec one command\n", 1);
/*	int	i;

	i = 0;
	v->cmd = ft_split(v->tab[0], ' ');
	if (!v->cmd)
		printf("error tab\n");
	if (v->cmd[0][0] == '<')
		i = ft_reverse_chevron(v->cmd);
	if (ft_check_outpout(v->cmd))
		ft_exec_outpout(v->cmd);
	v->cmd[i] = ft_suppr_dq_sq(v->cmd[i]);
	ft_is_builtin(v->cmd[i], v->tab);*/
}
