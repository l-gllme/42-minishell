/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/19 17:54:28 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int g_retour = 0;

void	handler(int signum)
{
	(void)signum;
	if (signum == 3)
	{
		g_retour = 131;
		printf("A faire...");
	}
	if (signum == 2)
	{
		g_retour = 130;
		write(0, "\n\033[34m➜\033[0m ", 15);
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	t_list	*exprt;


	list = init_lst(env, NULL);
	exprt = init_lst(env, NULL);
	(void)av;
	if (ac != 1)
		ft_error(2);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		str = readline("\033[34m➜\033[0m ");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
		{
			rl_clear_history();
			ft_lstclear(&list, &free);
			ft_lstclear(&exprt, &free);
			ft_exit(str);
		}
		if (str[0])
			add_history(str);
		if (str[0])
		{
			parsing(str, env, list, exprt);
		}
		free(str);
	}
	ft_lstclear(&list, &free);
	ft_lstclear(&exprt, &free);
	return (0);
}
