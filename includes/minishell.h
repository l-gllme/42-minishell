/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:57:05 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 17:23:17 by lguillau         ###   ########.fr       */
/*   Updated: 2022/05/06 15:44:26 by lguillau         ###   ########.fr       */
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
int		parsing(char *line, char **env, t_list *list);
int		ft_check_outpout(char **cmd);
void	init_struct(char **tab, t_g *v, char **env, t_list *list);
t_i		*ft_init_env_struct(t_i *env);
char	*ft_check_in_env(t_g *v, char *exec, int i);
char	*ft_check_in_env_2(t_g *v, char *exec, int i, char *str);
char	*ft_check_special(char *str, t_g *v);
char	*ft_recup_retour(char *str);
char	*ft_add_space_dol(char *str);
int		in_env(char *str, t_g *v);
int		ft_check_doll(char *str);
int		ft_env_while_2(t_i *env, int i, t_g *v, t_list *tmp);
int		ft_env_while(t_i *env, int i, t_g *v, t_list *tmp);
void	ft_recup_for_check_in_env_2(char *exec, t_i *env);
void	ft_recup_for_check_in_env(char *arg, t_i *env);
void	ft_recup_new_arg_2(t_i *env, char *recup, t_g *v, char *arg);
int		ft_check_for_env(t_i *env, t_list *tmp, int i, t_g *v);
int		ft_check_just_doll(t_i *env, int i);
int		check_not_followed_sign(t_g *v);

int		parse_cmd(t_g *v);

/* get_cmd */
int		get_cmd(char *str, char **tab);

/* in_out_parse */
int		ft_add_spaces(t_g *v, char c, int index);

/* check_syntax.c */
int		check_not_closed_pipes(char **tab);
int		count_pipes(char *str);
int		ft_check_invalid_signs(char *str, char c, int i, int count);

/* parsing_tools.c */
void	init_syntax_struct(t_s *s);
void	check_sq_dq(t_s *s_s, char c);
char	*ft_suppr_dq_sq(char *str);
int		count_signs(char **tab, char c);

/* stock_line */
char	**stock_in(t_g *v, char **in_tab, int i, int j);
char	**stock_out(t_g *v, char **out_tab, int i, int j);
char	*stock_exec(t_g *v, char *exec);
char	*stock_arg(t_g *v, char *arg);

/* ******************************* */
/*                                 */
/*               Exec              */
/*                                 */
/* ******************************* */

int		ft_exec(t_g *v, t_l *l);
int		ft_here_doc_no_cmd(char *limiter, t_g *v, t_l *tmp, int value);
void	handler(int signum);
void	ft_exec_cmd_test(t_l *tmp, t_g *v);
int		ft_exec_in_dup(t_g *v, char **tab, t_l *tmp, int choice);
int		create_tmp_file(t_l *tmp);
void	handler2(int signum);
void	ft_value_is_2(t_l *tmp);
void	ft_error_limiter(char *str);
void	ft_error_str_null(void);

/* ft_exec_in.c */
int		ft_exec_in(t_g *v, t_l *tmp, int c);
int		ft_exec_in_no_cmd(char **tab, int choice, t_g *v, t_l *tmp);
int		check_valid_infile(char *file);
int		check_valid_infile(char *file);



/* ft_exec_out.c */
int		ft_exec_out(t_g *v, t_l *tmp);
int		ft_exec_out_no_cmd(char **tab);

/* check_outfile.c */
int		check_outfile(char *file, int type);
int		check_dup_outfile(char *file, int type, t_l *tmp);

/* exec.c */
char	*try_access(char *cmd, t_g *v);
int		in_env_sans_dollard(char *str, t_g *v);
void	ft_fork_error(t_l *tmp, t_g *v, char **toto, char *stri);
void	ft_fork_str_null(int pipe_fd[2], t_g *v, char **toto, t_f *fork);
void	ft_out_tab_fork(t_f *in_fork, t_g *v, t_l *tmp);
void	ft_recup_arg_fork(t_f *in_fork, t_l *tmp);
int	ft_exec_cmd_no_redirect(t_g *v, t_l *tmp, char *str, int pipe_fd[2]);
int     ft_exec_one_cmd(t_g *v, char *str, t_l *tmp);


/* ft_is_builtin.c */
int		ft_is_builtin(char *str, t_g *v, int choice, t_l *tmp);

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
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_recup_name(char *name, char *env);
int		ft_lststrlen(char *str);
int		ft_check_equal(char *recup);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split_by_string(char *str, char *charset);
char	*ft_strcpy(char *dest, char *src);

/* str_tools.c */
char	*ft_itoa(int n);
int		ft_strlen(const char *s);
void	free_char_tab(char **s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* str_tools_2.c */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
char	**ft_tabdup(char **tab);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_tablen(char **tab);
char	*ft_strfind(char *big, char *little, size_t len);

/* split.c */
char	**ft_split(char const *s, char c);

/* supersplit.c */
char	**ft_supersplit(char *str, char c);
char	**ft_split_double(char *str, char *charset);

/* errors.c */
void	ft_error(int error);
int		ft_custom_error(char *str, int ret, t_g *v);
char	*ft_char_error(char *str, char *ret, t_g *v);
void	ft_free(t_g *v);

/* ******************************* */
/*                                 */
/*              lst                */
/*                                 */
/* ******************************* */

/* lst.c */
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstnew(char	*name, char *content, char *line);
t_list	*init_lst(char **env, t_list *list);
int		ft_lstsize(t_list *lst);

/* super_lst.c */
void	ft_super_lstclear(t_l	**lst, void (*del)(void *));
void	ft_super_lstdelone(t_l	*lst, void (*del)(void *));
t_l		*ft_super_lstnew(char **out_tab, char **in_tab, char *arg, char *exec);
void	ft_super_lstadd_back(t_l **alst, t_l *new);
t_l		*ft_super_lstlast(t_l *lst);
int		ft_super_lstsize(t_l *lst);

t_list	*ft_change_shlvl(t_list *list, char **env);

/* ******************************* */
/*                                 */
/*             Builtins            */
/*                                 */
/* ******************************* */

/* export.c */
int		in_env_sans_dollard(char *str, t_g *v);
char	*ft_recup_content(char *str, t_g *v);

#endif
