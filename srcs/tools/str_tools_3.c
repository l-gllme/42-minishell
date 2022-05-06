/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:39:00 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 14:41:32 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (0);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

char	**ft_tabdup(char **tab)
{
	char	**dup;
	int		len;
	int		i;

	i = -1;
	if (!tab)
		return (NULL);
	len = ft_tablen(tab);
	if (len == 0)
		return (NULL);
	dup = malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	while (++i < len)
		dup[i] = ft_strdup(tab[i]);
	dup[i] = 0;
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	return_val;

	i = 0;
	if (!dst || !src)
		return (0);
	return_val = ft_strlen(src);
	while (src[i] && i < (size - 1) && size != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = 0;
	return (return_val);
}

int	ft_tablen(char **tab)
{
	int	i;

	if (!tab || ft_strlen(tab[0]) == 0)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strfind(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
