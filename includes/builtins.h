/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:05:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/05 13:48:01 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "structs.h"

/* *** Echo *** */
void	ft_echo(char *str);
/* *** cd *** */
int	perm_cd(char *arg);
int	error_cd(char *arg);
int	cut_cd_no_arg_or_multiple(char *arg, t_g *v, int choice);
int	cut_cd_just_tild(char *arg, char *str, int *i);
int		ft_cd(char *arg, t_g *v);
/* *** pwd *** */
void	ft_pwd(void);
/* *** export *** */
void	ft_export(char *arg, t_g *v);
/* *** unset *** */
void	ft_unset(char *arg, t_g *v);
/* *** env *** */
void	ft_env(t_g *v);
/* *** exit *** */
void	ft_exit(char *line);

#endif
