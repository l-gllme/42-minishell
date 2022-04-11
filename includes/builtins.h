/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:05:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/11 18:18:34 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "structs.h"

/* *** Echo *** */
void	ft_echo(char *str);
/* *** cd *** */
int	ft_cd(char *arg);
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
