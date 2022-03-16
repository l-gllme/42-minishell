/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:05:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/16 17:18:58 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* *** Echo *** */
void	ft_echo(char **arg);
/* *** cd *** */
void	ft_cd(char *arg);
/* *** pwd *** */
void	ft_pwd(void);
/* *** export *** */
void	ft_export(char *arg);
/* *** unset *** */
void	ft_unset(char *arg);
/* *** env *** */
void	ft_env(void);
/* *** exit *** */
void	ft_exit(char *line);

#endif
