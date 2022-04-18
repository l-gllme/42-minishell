/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:07:13 by jtaravel          #+#    #+#             */
/*   Updated: 2022/04/18 14:15:18 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_check_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_countword(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_check_charset(charset, str[i]) == 1)
			i++;
		else
		{
			while (str[i] != '\0' && ft_check_charset(charset, str[i]) == 0)
				i++;
			count++;
		}
	}
	return (count);
}

int	ft_lenword(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_check_charset(charset, str[i]) == 0)
		i++;
	return (i);
}

char	*ft_cpyword(char *str, char *charset, int n)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_lenword(str, charset) + 1));
	if (!(cpy))
		return (0);
	while (str[i] != '\0' && i < n)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split_by_string(char *str, char *charset)
{
	int		i;
	int		j;
	char	**res;

	if (!str)
		return (0);
	res = malloc(sizeof(char *) * (ft_countword(str, charset) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_check_charset(charset, str[i]) == 1)
			i++;
		else
		{
			res[j] = ft_cpyword(str + i, charset, ft_lenword(str + i, charset));
			j++;
			i = i + ft_lenword(str + i, charset);
		}
	}
	res[j] = 0;
	return (res);
}
