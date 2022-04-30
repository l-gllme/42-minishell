/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:04:03 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/30 14:36:56 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


typedef struct s_list
{
	char			*name;
	char			*content;
	char			*line;
	struct s_list	*next;
}	t_list;

typedef struct s_line
{
	char	**in_tab;
	char	**out_tab;
	char	*exec;
	char	*arg;
	int		out;
	char	*name_out;
	int		in;
	char	*name_in;
	int		pipe;
	char	*name_pipe;
	struct s_line	*next;
}	t_l;

typedef struct s_global
{
	char	**env;
	char	**tab;
	char	**cmd;
	char	*wagon;
	char	*urandom;
	char	**new_env;
	char	*expor;
	char	*file_in;
	int		retour;
	int		dup_type;
	int		nb_built;
	int		fd_in;
	int		nb_cmd;
	int		access;
	int		tmp_file;
	t_list	*list;
	t_list	*exprt;
	t_l	*l;
}	t_g;

typedef struct s_syntax
{
	int	sq_opened;
	int	dq_opened;
}	t_s;

typedef struct s_get_cmd
{
	int		sq_opened;
	int		dq_opened;
	int		i;
	int		j;
	int		k;
	int		l;
}	t_c;

typedef struct g_minishell
{
	int	retour;
	char	*str;
	char	**split;
	char	*test;
	int	j;
	int	c;
	int	d;
	t_g *v;
}	t_shell;

extern t_shell	g_shell;

#endif
