/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/13 14:04:25 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

void	handler(int signum)
{
	if (signum == 3 && g_shell.in_exec == 1)
	{
		g_shell.retour = 131;
		exit(131);
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

static	void	ft_str_null(char *str, t_list *list)
{
	(void)str;
	rl_clear_history();
	ft_lstclear(&list, &free);
	printf("Bye! 👋\n");
	exit(0);
}

static void	ft_minishell(char *str, t_list *list, char **env, int i)
{
	if (g_shell.in_exec == 0)
		signal(SIGQUIT, SIG_IGN);
	if (g_shell.in_exec == 1)
		signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	str = readline("minishell$ ");
	if (str == NULL)
		ft_str_null(str, list);
	while (str[++i] == ' ')
		;
	if (i == ft_strlen(str))
	{
		free(str);
		return ;
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
		ft_minishell(str, list, env, -1);
	ft_lstclear(&list, &free);
	return (0);
}
