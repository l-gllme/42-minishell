/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/04 14:30:02 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

void	handler(int signum)
{
	if (signum == 3 && g_shell.in_exec == 1)
	{
		g_shell.retour = 131;
		printf("Quit (core dumped)\n");
	}
	if (signum == 2)
	{
		g_shell.retour = 130;
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signum == 3 && g_shell.in_exec == 0)
	{
		write (2, "lol\n", 4);
		
		g_shell.retour = 131;
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;

	g_shell.in_exec = 0;
	g_shell.retour = 0;
	list = NULL;
	list = init_lst(env, list);
	(void)av;
	if (ac != 1)
		ft_error(2);
	while (1)
	{
		if (g_shell.in_exec == 0)
			signal(SIGQUIT, SIG_IGN);
		if (g_shell.in_exec == 1)
		{
			printf ("lol\n");
			signal(SIGQUIT, handler);
		}
		signal(SIGINT, handler);
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
		g_shell.in_exec = 0;
	}
	ft_lstclear(&list, &free);
	return (0);
}
