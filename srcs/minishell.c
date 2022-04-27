/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/27 16:35:09 by jtaravel         ###   ########.fr       */
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
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;


	list = NULL;
	list = init_lst(env, list);
	(void)av;
	if (ac != 1)
		ft_error(2);
	while (1)
	{
		//signal(SIGINT, handler);
		//signal(SIGQUIT, handler);
		str = readline("\033[34m➜\033[0m ");
		if (str == NULL)
		{
			rl_clear_history();
			ft_lstclear(&list, &free);
			ft_exit(str);
		}
		if (str[0])
			add_history(str);
		if (str[0])
			parsing(str, env, list);
		free(str);
	}
	ft_lstclear(&list, &free);
	return (0);
}
