/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:21:51 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 15:00:33 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_check_name(char *split)
{
	int	i;

	if (!split)
		return (0);
	if (ft_isdigit(split[0]))
		return (0);
	i = 0;
	while (split[i])
	{
		if (ft_isalpha(split[i]) || ft_isdigit(split[i]) || split[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_already_in_env(char *split, t_g *v)
{
	t_list	*tmp;

	tmp = v->list;
	if (!split)
		return ;
	while (tmp)
	{
		if (tmp->name && !ft_strcmp(split, tmp->name))
		{
			ft_unset(split, v);
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	**ft_list_to_tab_for_exprt(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->exprt;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	if (!recup)
		return (NULL);
	i = 0;
	while (tmp)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	return (recup);
}

char	**ft_list_to_tab(t_g *v)
{
	t_list	*tmp;
	char	**recup;
	int		len;
	int		i;

	tmp = v->list;
	tmp = tmp->next;
	len = ft_lstsize(tmp);
	recup = malloc(sizeof(char *) * (len + 1));
	if (!recup)
		return (NULL);
	i = 0;
	while (tmp)
	{
		recup[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	recup[i] = 0;
	return (recup);
}
