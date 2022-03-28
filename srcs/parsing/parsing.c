/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/28 15:41:48 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parse_command(t_g *v, int nb)
{
	if (!ft_check_in_out(v, nb))
		return (-1);
	return (1);
}

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
		return (-1);
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

int	ft_add_spaces(t_g *v, char c)
{
	int	len;
	int	j;
	int	i;
	t_s	s;

	len = 0;
	i = 0;
	init_syntax_struct(&s);
	while (v->tab[0][i])
	{
		check_sq_dq_siuuuuu(&s, v->tab[0][i]);
		if (s.sq_opened == 0 && s.dq_opened == 0 && i != 0 && v->tab[0][i] == c)
		{
			if (v->tab[0][i - 1] != ' ' || v->tab[0][i - 1] != c)
				len++;
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[0][i] == c && v->tab[0][i + 1] == c)
		{
			i++;
			len++;
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[0][i] == c && c && v->tab[0][i + 1] != c)
			len++;
		i++;
	}
	len += ft_strlen(v->tab[0]);
	v->wagon = malloc(sizeof(char *) * (len + 1));
	if (!v->wagon)
		return (0);
	i = 0;
	j = 0;
	init_syntax_struct(&s);
	while (v->tab[0][i])
	{
		check_sq_dq_siuuuuu(&s, v->tab[0][i]);
		if (s.sq_opened == 0 && s.dq_opened == 0 && i != 0 && v->tab[0][i] == c)
		{
			if (v->tab[0][i - 1] != ' ' || v->tab[0][i - 1] != c)
				v->wagon[j++] = ' ';
		}
		v->wagon[j] = v->tab[0][i];
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[0][i] == c && v->tab[0][i + 1] == c)
		{
			v->wagon[j] = c;
			j++;
			i++;
			v->wagon[j] = ' ';
		}
		if (s.sq_opened == 0 && s.dq_opened == 0 && v->tab[0][i] == c && v->tab[0][i + 1] != c)
		{
			v->wagon[j] = c;
			j++;
			v->wagon[j] = ' ';
		}
		j++;
		i++;
	}
	v->wagon[j] = 0;
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
		v->nb_cmd = 1;
		ft_add_spaces(v, '<');
		v->cmd = ft_supersplit(v->wagon, ' ');
		//v->cmd = ft_split_double(v->tab[0], "<");
		if (!v->cmd || v->cmd[0][0] == 0)
		{
			free_char_tab(v->tab);
			free(v->arg);
			free(v);
			return (-1);
		}
		if(ft_reunite_central_arg(v) == -1)
		{
			free_char_tab(v->cmd);
			free_char_tab(v->tab);
			free(v->wagon);
			free(v->arg);
			free(v);
			return (-1);
		}
			
	}
	else if (i > 1)
	{
		v->nb_cmd = i;
		ft_putstr_fd("Multiple commands\n", 1);
	}
	return (1);
}

void	init_struct(char **tab, t_g *v)
{
	v->tab = tab;
	v->file_in = NULL;
	v->file_out = NULL;
	//v->arg = NULL;
	v->out = 0;
	v->in = 0;
	v->nb_cmd = 0;
	v->access = 0;
}

int	parsing(char *str, char **env)
{
	char	**tab;
	t_g	*v;

	tab = malloc(sizeof(char *) * count_pipes(str));
	v = malloc(sizeof(t_g));
	if (!v)
		ft_error(2);
	v->env = env;
	if (!tab)
		return (-1);
	if (get_cmd(str, tab) == -1)
		return (-1);
	if (check_not_closed_pipes(tab) == -1 || !ft_check_invalid_signs(str, '<') || !ft_check_invalid_signs(str, '>'))
		return (-1);
	init_struct(tab, v);
	if (parse_cmd(v) == -1)
		return (-1);
	if (v->nb_cmd == 1)
		ft_exec_one(v);
//	int	i = 0;
	//while (v->cmd[i])
//	{
//		printf("test = %s\n", v->cmd[i]);
//		i++;
//	}
	if (v->cmd)
		free_char_tab(v->cmd);
	free_char_tab(tab);
	free(v->wagon);
	free(v->arg);
	free(v);
	return (1);
}
