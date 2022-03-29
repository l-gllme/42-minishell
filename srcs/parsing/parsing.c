/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/29 14:34:56 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_access(char *cmd)
{
	int		i;
	char	**path;

	if (access(cmd, X_OK) == 0)
		return (1);
	path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
	}
	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
		{
			free_char_tab(path);
			return (1);
		}
	}
	free_char_tab(path);
	return (-1);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
	{
		ft_echo(ft_suppr_dq_sq(cmd));
		return (1);
	}
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
	{
		ft_pwd();
		return (1);
	}
	return (-1);
}

int	ft_reunite_central_arg(t_g *v)
{
	int	i;
	int	j;
	
	v->arg = malloc(sizeof(1));
	v->arg[0] = 0;
	i = 0; 
	while (v->cmd[i] && v->cmd[i][0] == '<' && v->cmd[i][1] == '<')
		i += 2;
	 if (!v->cmd[i])
		 return (-1);
	if (is_builtin(ft_suppr_dq_sq(v->cmd[i])) == 1)
		i++;
	else if (try_access(ft_suppr_dq_sq(v->cmd[i])) == 1)
	{
		v->access = 1;
		i++;
	}
	else
		return (0);
	j = i;
	v->built = v->cmd[i];
	while (v->cmd[j] && v->cmd[j][0] != '>')
	{
		if (j != i)
			v->arg = ft_strjoin(v->arg, " ");
		v->arg = ft_strjoin(v->arg, v->cmd[j]);
		j++;
	}
	return (1);
}

int	parse_cmd(t_g *v)
{
	int	i;

	i = -1;
	while (v->tab[++i])
		;
	if (i == 1)
	{
		if (!ft_add_spaces(v, '<', 0) || !ft_add_spaces(v, '>', 0))
			ft_custom_error(NULL, 0, v);
		v->nb_cmd = 1;
		v->cmd = ft_supersplit(v->tab[0], ' ');
		if (!v->cmd)
			return (ft_custom_error("error in ft_supersplit()\n", 0, v));
		if(!ft_reunite_central_arg(v))
			return (ft_custom_error(NULL, 0, v));
	}
	else if (i > 1)
	{
		v->nb_cmd = i;
		ft_putstr_fd("Multiple commands\n", 1);
		return (0);
	}
	return (1);
}

void	init_struct(char **tab, t_g *v, char **env)
{
	v->env = env;
	v->tab = tab;
	v->cmd = NULL;
	v->arg = NULL;
	v->nb_cmd = 0;
	v->access = 0;
}

int	parsing(char *str, char **env)
{
	char	**tab;
	t_g	*v;

	if (!ft_check_invalid_signs(str, '<') || !ft_check_invalid_signs(str, '>'))
		return (0);
	v = malloc(sizeof(t_g));
	if (!v)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	tab = malloc(sizeof(char *) * count_pipes(str));
	if (!tab)
		return (ft_custom_error("Malloc error in parsing()\n", 0, v));
	init_struct(tab, v, env);
	if (!get_cmd(str, tab))
		return (ft_custom_error(NULL, 0, v));
	if (!check_not_closed_pipes(tab))
		return (ft_custom_error(NULL, 0, v));
	if (!parse_cmd(v))
		return (0);
	if (v->nb_cmd == 1)
		ft_exec_one(v);
	return (1);
}
