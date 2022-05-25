/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:01:59 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/25 12:39:48 by jtaravel         ###   ########.fr       */
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
		if (env->split[i + 1] && g_shell.check)
		{
			g_shell.check--;
			recup = ft_strjoin_gnl(recup, " ");
		}
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

void	ft_while(t_i *env, int i, t_g *v, t_list *tmp)
{
	while (env->l == 1 && env->split[i])
	{
		if (!ft_env_while_2(env, i, v, tmp))
			break ;
		i++;
	}
}

char	*ft_check_in_env_2(t_g *v, char *exec, int i, char *arg)
{
	char	*recup;
	t_i		env;
	t_list	*tmp;

	tmp = NULL;
	ft_init_env_struct(&env);
	recup = NULL;
	if (exec)
		ft_recup_for_check_in_env_2(exec, &env);
	else
		return (NULL);
	if (env.l == 1)
	{
		ft_while(&env, i, v, tmp);
		recup = ft_recup_new(&env, recup);
	}
	else
		return (exec);
	if (!arg && env.l == 1)
		ft_recup_new_arg_2(&env, recup, v, arg);
	return (recup);
}
