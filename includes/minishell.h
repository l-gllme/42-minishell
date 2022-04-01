/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:57:05 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/01 18:12:51 by jtaravel         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <linux/random.h>

# include "get_next_line.h"
# include "builtins.h"
# include "structs.h"

/* ******************************* */
/*                                 */
/*             Parsing             */
/*                                 */
/* ******************************* */

/* parsing.c */
int		parsing(char *line, char **env);
int		ft_check_outpout(char **cmd);
void	init_struct(char **tab, t_g *v, char **env);

/* get_cmd */
int		get_cmd(char *str, char **tab);

/* in_out_parse */
int		ft_add_spaces(t_g *v, char c, int index);

/* check_syntax.c */
int		check_not_closed_pipes(char **tab);
int		count_pipes(char *str);
int		ft_check_invalid_signs(char *str, char c);

/* parsing_tools.c */
void	init_syntax_struct(t_s *s);
void	check_sq_dq(t_s *s_s, char c);
char	*ft_suppr_dq_sq(char *str);

/* stock_line */
int	stock_in(t_g *v);
int	stock_out(t_g *v);
int	stock_exec(t_g *v);
int	stock_arg(t_g *v);

/* ******************************* */
/*                                 */
/*               Exec              */
/*                                 */
/* ******************************* */

/* exec.c */
void	ft_exec_one(t_g *v);
int		ft_here_doc(char *limiter, t_g *v);

/* in_exec.c */
int		check_valid_infile(char *file);
int		redirect_in(t_g *v);
int		exec_in(t_g *v, char **tab);


/* ******************************* */
/*                                 */
/*              Tools              */
/*                                 */
/* ******************************* */

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
int		ft_tablen(char **tab);

/* split.c */
char	**ft_split(char const *s, char c);

/* supersplit.c */
char	**ft_supersplit(char *str, char c);
char	**ft_split_double(char *str, char *charset);

/* errors.c */
void	ft_error(int error);
int		ft_custom_error(char *str, int ret, t_g *v);
void	ft_free(t_g *v);

#endif
