/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_tools_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:30:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 15:14:38 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

int	in_env(char *str, t_g *v)
{
	int		i;
	t_list	*tmp;

	i = 0;
	str = ft_strdup(str + 1);
	tmp = v->list;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	free(str);
	return (0);
}

char	*ft_recup_for_retour(char *str, char *recup, int i, char *tmp)
{
	int	j;
	int	c;

	c = 0;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			while (c < ft_strlen(tmp))
			{
				recup[j] = tmp[c];
				c++;
				j++;
			}
			i += 1;
		}
		else
		{
			recup[j] = str[i];
			j++;
		}
	}
	recup[j] = 0;
	return (recup);
}

char	*ft_recup_retour(char *str)
{
	int		i;
	char	*tmp;
	char	*recup;

	tmp = ft_itoa(g_shell.retour);
	recup = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp)));
	i = 0;
	if (str[i] == ' ')
		i++;
	recup = ft_recup_for_retour(str, recup, i - 1, tmp);
	free(str);
	free(tmp);
	return (recup);
}

char	*ft_recup_add_space(char *res, char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			res[c] = ' ';
			c++;
		}
		res[c] = str[i];
		i++;
		c++;
	}
	res[c] = 0;
	return (res);
}
