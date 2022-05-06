/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:27:35 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/06 13:28:07 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_export_no_in_env(char *recup, char *line, t_g *v, char *arg)
{
	line = ft_strjoin_gnl(line, recup);
	line = ft_strjoin_gnl(line, arg + ft_strlen(recup) + 1);
	ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(recup),
			ft_strdup(arg + ft_strlen(recup) + 1), line));
}

void	ft_export_plus_equal_no_content(char *recup, t_g *v, char *line)
{
	line = ft_strjoin(recup, "=""");
	ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(recup),
			ft_strdup(line + ft_strlen(recup)), ft_strdup(line)));
}

int	ft_export_plus_equal(char *arg, t_g *v, int i)
{
	char	*line;
	char	*recup;

	line = NULL;
	recup = ft_recup_correct_export(arg);
	while (arg[++i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=' && arg[i - 1] != '+')
		{
			if (!in_env_sans_dollard(recup, v))
			{
				if (arg[ft_strlen(arg) - 1] == '=')
					ft_export_plus_equal_no_content(recup, v, line);
				else
					ft_export_no_in_env(recup, line, v, arg);
			}
			else
				ft_export_plus_equal_2(v, recup, arg);
			if (recup)
				free(recup);
			return (1);
		}
	}
	free(recup);
	return (0);
}

void	*ft_memcpy(const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	char		*cpydest;
	const char	*cpysrc;

	if (!src)
		return (NULL);
	i = 0;
	if (n <= 0)
		return (NULL);
	dest = malloc(sizeof(char) * (n + 1));
	cpydest = dest;
	cpysrc = src;
	while (i < n)
	{
		cpydest[i] = cpysrc[i];
		i++;
	}
	cpydest[i] = 0;
	dest = cpydest;
	return (dest);
}

void	ft_normal_export_2(t_g *v, char **split, char **recup, int i)
{
	char	*tmp;

	ft_suppr_dq_sq(recup[i]);
	split = ft_split(recup[i], '=');
	tmp = ft_strdup(split[1]);
	free(split[1]);
	split[1] = ft_strjoin("=", tmp);
	free(tmp);
	if (!ft_check_name(split[0]))
	{
		printf("Minishell: export: '%s': not a valid identifier\n",
			recup[i]);
		g_shell.retour = 1;
	}
	else
		ft_lstadd_back(&v->list, ft_lstnew(ft_strdup(split[0]),
				ft_strdup(split[1]), ft_strdup(recup[i])));
	free_char_tab(split);
}
