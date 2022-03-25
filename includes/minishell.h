/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:57:05 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/25 14:09:43 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "get_next_line.h"
# include "builtins.h"
# include "structs.h"

/* *** *** Parsing *** *** */

/* parsing.c */
int		parsing(char *line, t_g *v);
int		ft_check_outpout(char **cmd);
void	init_struct(char **tab, t_g *v);

/* get_cmd */
int		get_cmd(char *str, char **tab);

/* in_out_parse */
int		ft_check_in_out(t_g *v, int nb);

/* check_syntax.c */
int		check_not_closed_pipes(char **tab);
int		count_pipes(char *str);

/* parsing_tools.c */
void	init_syntax_struct(t_s *s);
char	*ft_suppr_dq_sq(char *str);

/* *** *** Parsing *** *** */

/* exec.c */
void	ft_exec_one(t_g *v);
int	ft_here_doc(char *limiter, t_g *v);

/* *** *** Tools *** *** */

/* tools.c */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

/* str_tools.c */
int		ft_strlen(const char *s);
void	free_char_tab(char **s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* str_tools_2.c */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* split.c */
char	**ft_split(char const *s, char c);

/* supersplit.c */
char	**ft_supersplit(char *str, char c);
void	check_sq_dq_siuuuuu(t_s *s_s, char c);
char	**ft_split_double(char *str, char *charset);

/* errors.c */
void	ft_error(int error);

#endif
