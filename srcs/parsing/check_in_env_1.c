/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:12:56 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/09 15:58:07 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	ft_start_while_2(t_i *env, int i)
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

int	ft_env_while(t_i *env, int i, t_g *v, t_list *tmp)
{
	printf ("split1 = %s\n", env->split[i]);
	ft_start_while_2(env, i);
	env->split[i] = ft_check_special(env->split[i], v, 0);
	printf ("split2 = %s\n", env->split[i]);
	env->split[i] = ft_recup_retour(env->split[i]);
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

void	ft_recup_for_check_in_env(char *arg, t_i *env)
{
	char	*test;

	if (!ft_check_doll(arg))
		env->l = 0;
	else
	{
		env->l = 1;
		test = ft_strdup(arg);
		free(arg);
		arg = ft_add_space_dol(test);
		free(test);
		env->split = ft_supersplit(arg, ' ');
		free(arg);
	}
}
