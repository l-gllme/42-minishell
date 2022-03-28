/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:04:03 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/28 14:27:10 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_global
{
	char	**env;
	char	**tab;
	char	**cmd;
	char	*wagon;
	char	*built;
	int		nb_cmd;
	int		out;
	int		in;
	int		access;
	char	*file_in;
	char	*file_out;
	char	*arg;
}	t_g;

typedef struct s_syntax
{
	int	sq_opened;
	int	dq_opened;
	int	stat;
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

#endif
