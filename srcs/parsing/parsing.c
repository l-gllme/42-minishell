/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:08:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/04 16:48:42 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_not_followed_sign(char *str)
{
	t_s	s;
	int	i;

	i = ft_strlen(str);
	init_syntax_struct(&s);
	check_sq_dq(&s, str[i]);
	while (str[--i] == ' ' && !s.sq_opened && !s.dq_opened)
		;
	if (str[i] == '>' || str[i] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}

/*int	ft_reunite_central_arg(t_g *v)
{
	int	i;
	int	j;
	
	v->arg = malloc(sizeof(1));
	v->arg[0] = 0;
	i = 0; 
	j = 0;
	while (v->cmd[j])
	{
		printf("str=%s\n", v->cmd[j]);
		j++;
	}
	while (v->cmd[i] && v->cmd[i][0] == '<' && v->cmd[i][1] == '<')
	{
		printf("test = %s\n", v->cmd[i + 1]);
		ft_here_doc(v->cmd[i + 1], v);
		i += 2;
	}
	 if (!v->cmd[i])
		 return (0);
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
	v->funct = v->cmd[i];
	while (v->cmd[j] && v->cmd[j][0] != '>')
	{
		if (j != i)
			v->arg = ft_strjoin(v->arg, " ");
		v->arg = ft_strjoin(v->arg, v->cmd[j]);
		j++;
	}
	return (1);
}*/

int	parse_cmd(t_g *v)
{
	int	i;

	i = -1;
	while (v->tab[++i])
		;
	if (i == 1)
	{
		if (!ft_add_spaces(v, '<', 0) || !ft_add_spaces(v, '>', 0))
			return (ft_custom_error(NULL, 0, v));
		if (!check_not_followed_sign(v->tab[0]))
			return (ft_custom_error(NULL, 0, v));
		v->nb_cmd = 1;
		v->cmd = ft_supersplit(v->tab[0], ' ');
		if (!v->cmd)
			return (ft_custom_error("error in ft_supersplit()\n", 0, v));
		if (!stock_in(v))
			return (ft_custom_error("malloc error in stock_in()\n", 0, v));
		if (!stock_out(v))
			return (ft_custom_error("malloc error in stock_in()\n", 0, v));
		if (!stock_exec(v))
			return (ft_custom_error("error in stock_exec()\n", 0, v));
		if (!stock_arg(v))
			return (ft_custom_error("error in stock_arg()\n", 0, v));
		//if(!ft_reunite_central_arg(v))
		//	return (ft_custom_error(NULL, 0, v));
	}
	else if (i > 1)
	{
		v->nb_cmd = i;
		return (ft_custom_error("Multiple commands\n", 0, v));
	}
	return (1);
}

void	init_struct(char **tab, t_g *v, char **env)
{
	v->env = env;
	v->tab = tab;
	v->cmd = NULL;
	v->nb_cmd = 0;
	v->access = 0;
	v->l.in_tab = NULL;
	v->l.out_tab = NULL;
	v->l.exec = NULL;
	v->l.arg = NULL;
	//v->fd_in = 0;
	//v->file_in = NULL;
	//v->urandom = NULL;
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
	//ft_free(v);
	return (1);
}
