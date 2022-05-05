/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:01:59 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/05 19:25:59 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_i	*ft_init_env_struct(t_i *env)
{
	env->j = 0;
	env->l = 0;
	env->d = 0;
	env->c = 0;
	return (env);
}

char	*ft_recup_new(t_i *env, char *recup)
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
		if (env->split[i + 1] && g_shell.retour != 7)
			recup = ft_strjoin_gnl(recup, " ");
		i++;
	}
	if (ft_strlen(recup) > 0 && recup[ft_strlen(recup) - 1] == ' ')
		recup[ft_strlen(recup) - 1] = 0;
	free_char_tab(env->split);
	return (recup);
}

void	ft_no_in_env(t_i *env, t_list *tmp, char *test, int i)
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
		return (2);
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

int	ft_check_just_doll(t_i *env, int i)
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

int	ft_env_while(t_i *env, int i, t_g *v, t_list *tmp)
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
		if (ft_check_for_env(env, tmp, i, v) == 2)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_recup_for_check_in_env(char *exec, t_i *env)
{
	char	*test;

	if (!ft_check_doll(exec))
		env->l = 0;
	else
		env->l = 1;
	test = ft_strdup(exec);
	free(exec);
	exec = ft_add_space_dol(test);
	free(test);
	env->split = ft_supersplit(exec, ' ');
	free(exec);
}

char	*ft_check_in_env_2(t_g *v, char *exec, int i, char *arg)
{
	char	*recup;
	t_i		env;
	t_list	*tmp;
	char	*test;

	tmp = NULL;
	ft_init_env_struct(&env);
	recup = NULL;
	if (exec)
		ft_recup_for_check_in_env(exec, &env);
	else
		return (NULL);
	while (env.split[i] && env.l == 1)
	{
		if (!ft_env_while(&env, i, v, tmp))
			break ;
		i++;
	}
	recup = ft_recup_new(&env, recup);
	if (!arg)
	{
		env.split = ft_supersplit(recup, ' ');
		free(recup);
		recup = ft_strdup(env.split[0]);
		i = 1;
		while (env.split[i])
		{
			arg = ft_strjoin_gnl(arg, env.split[i]);
			test = ft_strdup(arg);
			free(arg);
			arg = ft_strjoin(" ", test);
			free(test);
			i++;
		}
		v->l->arg = ft_strdup(arg);
		free(arg);
		free_char_tab(env.split);
	}
	return (recup);
}
