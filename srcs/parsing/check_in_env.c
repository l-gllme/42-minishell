/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:01:59 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/05 19:28:55 by jtaravel         ###   ########.fr       */
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
		if (env->split[i + 1])
			recup = ft_strjoin_gnl(recup, " ");
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

static	int	ft_check_for_env(t_i *env, t_list *tmp, int i, t_g *v)
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

static	int	ft_check_just_doll(t_i *env, int i)
{
	if (env->split[i][0] == '$' && env->split[i][1] == '$'
		&& env->split[i][2] == 0)
		return (0);
	if (env->split[i][0] == '$' && env->split[i][1] == 0)
		return (0);
	while (env->split[i][ft_strlen(env->split[i]) - 1] == '$'
		&& ft_strlen(env->split[i]) != 1)
	{
		env->split[i][ft_strlen(env->split[i]) - 1] = '\0';
		env->d++;
	}
	return (1);
}

static	int	ft_env_while(t_i *env, int i, t_g *v, t_list *tmp)
{
	env->c = 1;
	env->split[i] = ft_check_special(env->split[i], v);
	env->split[i] = ft_recup_retour(env->split[i]);
	ft_suppr_dq_sq(env->split[i]);
	if (!ft_check_just_doll(env, i))
		return (0);
	tmp = v->list;
	tmp = tmp->next;
	while (tmp && env->split[i][0] == '$')
	{
		if (!ft_check_for_env(env, tmp, i, v))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static	void	ft_recup_for_check_in_env(char *arg, t_i *env)
{
	char	*test;

	if (!ft_check_doll(arg))
		env->l = 0;
	else
		env->l = 1;
	test = ft_strdup(arg);
	free(arg);
	arg = ft_add_space_dol(test);
	free(test);
	env->split = ft_supersplit(arg, ' ');
	free(arg);
}

char	*ft_check_in_env(t_g *v, char *arg, int i)
{
	char	*recup;
	t_i		env;
	t_list	*tmp;

	tmp = NULL;
	ft_init_env_struct(&env);
	recup = NULL;
	if (arg)
		ft_recup_for_check_in_env(arg, &env);
	else
		return (NULL);
	while (env.split[i] && env.l == 1)
	{
		if (!ft_env_while(&env, i, v, tmp))
			i++;
		else
			i++;
	}
	recup = ft_recup_new(&env, recup);
	return (recup);
}
