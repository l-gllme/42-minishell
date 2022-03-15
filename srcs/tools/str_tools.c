/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:31:13 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/15 15:47:01 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_char_tab(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

static char	*ft_strjoin2(char *s1, char *s2, char *join)
{
	int	i;

	i = 0;
	while (*s1)
	{
		join[i] = *s1;
		s1++;
		i++;
	}
	join[i] = '/';
	i++;
	while (*s2)
	{
		join[i] = *s2;
		s2++;
		i++;
	}
	join[i] = 0;
	return (join);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_lenght;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	total_lenght = (ft_strlen(s1) + ft_strlen(s2) + 2);
	join = malloc(sizeof(char *) * total_lenght);
	if (!join)
		return (NULL);
	join = ft_strjoin2(s1, s2, join);
	free(s1);
	return (join);
}
