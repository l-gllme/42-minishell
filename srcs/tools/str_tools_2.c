/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:21 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 18:16:28 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[j + i] == needle[j] && needle[j] && j + i < len)
			{
				j++;
				if (!needle[j] && haystack[j + i])
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}

int	count_signs(char **tab, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (tab[++i])
	{
		if (tab[i][0] == c)
		{
			count++;
			if (tab[i + 1])
				i++;
		}
	}
	return (count);
}

void	ft_error_in_get_cmd(char **tab)
{
	tab[0] = 0;
	ft_putstr_fd("invalid syntax\n", 2);
}
