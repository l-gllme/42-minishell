/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:01:28 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/25 17:29:16 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_charset(char *charset, char c, t_s *s_s)
{
	int	i;

	i = 0;
	while (charset[i] != '\0' && s_s->sq_opened == 0 && s_s->dq_opened == 0)
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
	t_s	s_s;

	init_syntax_struct(&s_s);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		check_sq_dq_siuuuuu(&s_s, str[i]);
		if (ft_check_charset(charset, str[i], &s_s) == 1 && ft_check_charset(charset, str[i + 1], &s_s) == 1)
		{
			printf(";p;");
			i += 2;
		}
		else
		{
			while (str[i] != '\0' && (ft_check_charset(charset, str[i], &s_s) == 0 || ft_check_charset(charset, str[i + 1], &s_s) == 0))
				i++;
			count++;
		}
	}
	printf("count:%d\n", count);
	return (count);
}

int	ft_lenword(char *str, char *charset, t_s *s_s)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (ft_check_charset(charset, str[i], s_s) == 0 || ft_check_charset(charset, str[i + 1], s_s) == 0 ))
	{
		check_sq_dq_siuuuuu(s_s, str[i]);
		i++;
	}
	return (i);
}

char	*ft_cpyword(char *str, char *charset, int n, t_s *s_s)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_lenword(str, charset, s_s) + 1));
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

char	**ft_split_double(char *str, char *charset)
{
	int		i;
	int		j;
	char	**res;
	t_s		s_s;

	init_syntax_struct(&s_s);
	if (!str)
		return (0);
	res = malloc(sizeof(char *) * (ft_countword(str, charset) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_check_charset(charset, str[i], &s_s) == 1 && str[i] == str[i + 1])
			i += 2;
		else
		{
			res[j] = ft_cpyword(str + i, charset, ft_lenword(str + i, charset, &s_s), &s_s);
			j++;
			i = i + ft_lenword(str + i, charset, &s_s);
		}
	}
	res[j] = 0;
	return (res);
}
