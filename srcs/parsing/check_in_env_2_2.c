/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_2_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:10:47 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/09 16:48:48 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_start_while(t_i *env, int i)
{
	char	*temp;

	env->c = 1;
	ft_suppr_dq_sq(env->split[i]);
	if (env->split[i][0] == ' ')
	{
		temp = ft_strdup(env->split[i] + 1);
		free(env->split[i]);
		env->split[i] = temp;
	}
}

int	ft_env_while_2(t_i *env, int i, t_g *v, t_list *tmp)
{
	ft_start_while(env, i);
	env->split[i] = ft_check_special(env->split[i], v, 0);
	env->split[i] = ft_recup_retour(env->split[i]);
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

void	ft_recup_for_check_in_env_2(char *exec, t_i *env)
{
	char	*test;

	if (!ft_check_doll(exec))
		env->l = 0;
	else
	{
		env->l = 1;
		test = ft_strdup(exec);
		free(exec);
		exec = ft_add_space_dol(test);
		free(test);
		env->split = ft_supersplit(exec, ' ');
		free(exec);
	}
}

void	ft_recup_new_arg_2(t_i *env, char *recup, t_g *v, char *arg)
{
	int		i;
	char	*test;

	env->split = ft_supersplit(recup, ' ');
	recup = ft_strdup(env->split[0]);
	i = 0;
	while (env->split[i])
	{
		if (i == 0)
			i++;
		else
		{
			arg = ft_strjoin_gnl(arg, env->split[i]);
			test = ft_strdup(arg);
			free(arg);
			arg = ft_strjoin(" ", test);
			free(test);
			i++;
		}
	}
	v->l->arg = ft_strdup(arg);
	free(recup);
	free(arg);
	free_char_tab(env->split);
}
