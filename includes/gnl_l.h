/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_l.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:44:39 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/12 15:09:47 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_L_H
# define GNL_L_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"

char	*get_next_line(int fd);

/* -- GNL FUNCTS -- */

char	*get_read(char *save, int fd);
char	*get_line(char *save);
char	*cut_save(char	*save);

/* -- UTILS FUNCTS -- */

char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen2(const char *s);

#endif
