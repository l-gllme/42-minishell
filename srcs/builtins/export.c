/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:35:14 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 13:28:49 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_normal_export(t_g *v, char **split, char **recup, int i)
{
	char	*tmp;

	ft_already_in_env(split[0], v);
	if (recup[i][ft_strlen(recup[i]) - 1] == '=')
	{
		tmp = ft_memcpy(recup[i], ft_strlen(recup[i]) - 1);
		if (!ft_check_name(tmp))
		{
			printf("Minishell: export: '%s': not a valid identifier\n",
				recup[i]);
			g_shell.retour = 1;
		}
		else
			ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(split[0]),
					NULL, ft_strdup(recup[i])));
		free(tmp);
	}
	else
		ft_normal_export_2(v, split, recup, i);
}

void	ft_export_3(char **recup, int i, t_g *v)
{
	if (!ft_check_name(recup[i]))
	{
		printf("Minishell: export: '%s': not a valid identifier\n",
			recup[i]);
		g_shell.retour = 1;
	}
	else
		ft_put_in_export(recup[i], v);
}

void	ft_export_2(t_g *v, char **recup, int i, char **split)
{
	if (!ft_check_name(split[0]) || (recup[i][0] == '+'
		&& recup[i][1] == '=') || recup[i][0] == '=')
	{
		printf("Minishell: export: '%s': not a valid identifier\n",
			recup[i]);
		g_shell.retour = 1;
	}
	else if (!ft_check_equal(recup[i]))
		ft_export_3(recup, i, v);
	else if (!ft_export_plus_equal(recup[i], v, -1))
		ft_normal_export(v, split, recup, i);
}

void	ft_export(char *arg, t_g *v)
{
	char	**recup;
	char	**split;
	int		i;

	i = -1;
	if (!arg)
	{
		ft_export_no_arg(v);
		return ;
	}
	recup = ft_supersplit(arg, ' ');
	while (recup[++i] && arg)
	{
		split = ft_split_by_string(recup[i], "+=");
		ft_export_2(v, recup, i, split);
		free_char_tab(split);
	}
	free_char_tab(recup);
}
