/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/09 13:22:32 by lguillau         ###   ########.fr       */
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
		g_shell.retour = 131;
	}
	else
		return ;
}

void	ft_minishell(char *str, t_list *list, char **env)
{
	if (g_shell.in_exec == 0)
		signal(SIGQUIT, SIG_IGN);
	if (g_shell.in_exec == 1)
		signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	str = readline("\033[34m➜\033[0m ");
	if (str == NULL)
	{
		rl_clear_history();
		ft_lstclear(&list, &free);
		printf("Bye! 👋\n");
		ft_exit(str);
	}
	if (str[0])
		add_history(str);
	if (str[0])
		parsing(str, env, list, 0);
	free(str);
	g_shell.in_exec = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;

	str = NULL;
	g_shell.in_exec = 0;
	g_shell.retour = 0;
	list = NULL;
	list = init_lst(env, list);
	(void)av;
	if (ac != 1)
		ft_error(2);
	while (1)
		ft_minishell(str, list, env);
	ft_lstclear(&list, &free);
	return (0);
}
