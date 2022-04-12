/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:35:02 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/12 15:08:15 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 1

char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_get_line(char *str);
char	*ft_next_line(char *str);
char	*ft_read(char *tmp, int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_bzero(void *s, size_t n);

#endif
