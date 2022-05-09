/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:25:29 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 17:54:40 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_add_space_dol(char *str)
{
	int		i;
	int		c;
	char	*res;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
			c++;
		i++;
	}
	res = malloc(sizeof(char) * ((c + i) + 1));
	if (!res)
		return (NULL);
	res = ft_recup_add_space(res, str);
	return (res);
}

int	ft_check_doll(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_check_special_3(char *test, int len, char *str, char *res)
{
	free(test);
	test = ft_strdup(str + len);
	res = ft_strjoin_gnl(res, test);
	free(test);
	free(str);
	return (res);
}

char	*ft_check_special_2(t_list *tmp, char *res, char *str, char *test)
{
	int	len;

	len = ft_strlen(test) + 1;
	while (tmp)
	{
		if (!ft_strcmp(test, tmp->name))
		{
			if (tmp->content)
			{
				free(res);
				res = ft_strdup(tmp->content + 1);
			}
			else
			{
				free(res);
				res = ft_strdup("");
			}
			break ;
		}
		tmp = tmp->next;
	}
	res = ft_check_special_3(test, len, str, res);
	return (res);
}

char	*ft_check_special(char *str, t_g *v, int i)
{
	int		c;
	char	*res;
	t_list	*tmp;
	char	*test;

	tmp = v->list;
	c = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && !ft_isalpha(str[i])) && str[i] != '$'
			&& str[i + 1] != '?' && str[i] != '_' && str[i] != '+')
			break ;
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	if (ft_strlen(str) == ft_strlen(res))
	{
		free(res);
		return (str);
	}
	test = ft_strdup(res + 1);
	res = ft_check_special_2(tmp, res, str, test);
	return (res);
}
