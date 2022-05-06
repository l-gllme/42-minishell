/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:05:42 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:21:39 by lguillau         ###   ########.fr       */
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
void	ft_export_2(t_g *v, char **recup, int i, char **split);
void	ft_export_3(char **recup, int i, t_g *v);
void	ft_normal_export(t_g *v, char **split, char **recup, int i);
void	ft_normal_export_2(t_g *v, char **split, char **recup, int i);
void	*ft_memcpy(const void *src, size_t n);
int	ft_export_plus_equal(char *arg, t_g *v, int i);
void	ft_export_plus_equal_no_content(char *recup, t_g *v, char *line);
void	ft_export_no_in_env(char *recup, char *line, t_g *v, char *arg);
void	ft_export_plus_equal_2(t_g *v, char *recup, char *arg);
void	ft_export_plus_equal_3(t_g *v, char *recup, char *arg, char *test);
char	*ft_recup_correct_export(char *str);
int	in_env_sans_dollard(char *str, t_g *v);
void	ft_put_in_export(char *arg, t_g *v);
int	ft_check_equal(char *recup);
void	ft_export_no_arg(t_g *v);
t_list	*tab_to_list(char **env, t_list *list);
char	**ft_sort_ascii(char **av);
char	**ft_list_to_tab(t_g *v);
char	**ft_list_to_tab_for_exprt(t_g *v);
void	ft_already_in_env(char *split, t_g *v);
int	ft_check_name(char *split);
void	ft_export(char *arg, t_g *v);
/* *** unset *** */
void	ft_unset(char *arg, t_g *v);
/* *** env *** */
void	ft_env(t_g *v);
/* *** exit *** */
void	ft_exit(char *line);

#endif
