/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:49:00 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/15 15:54:36 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*str;

	if (fd == 42)
	{
		free(save[0]);
		return (NULL);
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save[fd] = get_read(save[fd], fd);
	if (!save[fd])
	{
		free(save[fd]);
		return (NULL);
	}
	str = get_line(save[fd]);
	save[fd] = cut_save(save[fd]);
	return (str);
}

char	*get_read(char *save, int fd)
{
	char	*str;
	int		ret;

	ret = 1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (!ft_strchr(save, '\n') && ret != 0)
	{
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == -1)
		{
			free(str);
			return (NULL);
		}
		str[ret] = 0;
		save = ft_strjoin2(save, str);
	}
	free(str);
	return (save);
}

char	*get_line(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (save[i] == 0)
		return (NULL);
	while (save[i] != '\n' && save [i])
		i++;
	if (save[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (save[++i] != '\n' && save[i])
		str[i] = save[i];
	if (save[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*cut_save(char	*save)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == 0)
	{
		free(save);
		return (NULL);
	}
	str = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!str)
		return (NULL);
	i++;
	while (save[i + j])
	{
		str[j] = save[i + j];
		j++;
	}
	str[j] = 0;
	free(save);
	return (str);
}
