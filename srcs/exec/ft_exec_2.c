/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:22:38 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 16:25:08 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_builtin(t_g *v, t_l *tmp)
{
	int	fd;

	if (!ft_exec_out(v, tmp))
		return (0);
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
	if (str == NULL && ft_recup_content("PATH", v) != NULL)
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
