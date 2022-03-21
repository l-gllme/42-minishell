/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:57:05 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/21 15:08:42 by lguillau         ###   ########.fr       */
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

typedef	struct s_global
{
	char	**env;
	char	**tab;
	char	**cmd;
}	t_g;

/* *** *** Parsing *** *** */

int	parsing(char *line, t_g *v);

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

/* split.c */
char	**ft_split(char const *s, char c);

/* errors.c */
void	ft_error(int error);

#endif
