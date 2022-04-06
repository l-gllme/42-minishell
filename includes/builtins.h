/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:05:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/06 16:52:38 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* *** Echo *** */
void	ft_echo(char *str);
/* *** cd *** */
int	ft_cd(char *arg);
/* *** pwd *** */
void	ft_pwd(void);
/* *** export *** */
void	ft_export(char *arg);
/* *** unset *** */
void	ft_unset(char *arg, char **env);
/* *** env *** */
void	ft_env(char **env);
/* *** exit *** */
void	ft_exit(char *line);

#endif
