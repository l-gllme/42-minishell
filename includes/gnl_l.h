/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:44:39 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/15 16:30:17 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

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
