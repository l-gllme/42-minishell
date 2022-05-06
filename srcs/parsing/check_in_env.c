/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:01:59 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/06 17:18:35 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*ft_recup_new(t_i *env, char *recup)
{
	int	i;

	i = 0;
	while (env->split[i])
	{
		recup = ft_strjoin_gnl(recup, env->split[i]);
		if (env->d)
		{
			recup = ft_strjoin_gnl(recup, "$");
			env->d--;
		}
		i++;
	}
	if (ft_strlen(recup) > 0 && recup[ft_strlen(recup) - 1] == ' ')
		recup[ft_strlen(recup) - 1] = 0;
	free_char_tab(env->split);
	return (recup);
}

static	void	ft_no_in_env(t_i *env, t_list *tmp, char *test, int i)
{
	if (tmp->content)
	{
		free(env->split[i]);
		env->split[i] = ft_strdup(tmp->content + 1);
	}
	else
	{
		free(env->split[i]);
		env->split[i] = ft_strdup("");
	}
	free(env->name);
	free(test);
}

int	ft_check_for_env(t_i *env, t_list *tmp, int i, t_g *v)
{
	char	*test;

	env->name = ft_strjoin("$", tmp->name);
	test = ft_strdup(env->split[i]);
	if (!ft_strncmp(env->split[i], env->name, ft_strlen(env->split[i]))
		&& in_env(env->split[i], v))
	{
		ft_no_in_env(env, tmp, test, i);
		return (0);
	}
	else if (!in_env(test, v))
	{
		free(env->split[i]);
		env->split[i] = ft_strdup("");
	}
	free(env->name);
	free(test);
	return (1);
}

char	*ft_check_in_env(t_g *v, char *arg, int i)
{
	char	*recup;
	t_i		env;
	t_list	*tmp;

	tmp = NULL;
	recup = NULL;
	ft_init_env_struct(&env);
	if (!arg)
		return (NULL);
	ft_recup_for_check_in_env(arg, &env);
	if (env.l == 1)
	{
		while (env.split[i] && env.l == 1)
		{
			if (!ft_env_while(&env, i, v, tmp))
				env.l = 1;
			i++;
		}
	}
	if (env.l == 1)
	{
		recup = ft_recup_new(&env, recup);
		return (recup);
	}
	return (arg);
}
