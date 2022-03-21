/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/21 16:06:56 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signum)
{
	(void)signum;
}

void exec_ls(char **env)
{
	char **toto;
	toto = malloc(sizeof(char *) * 2);
	toto[0] = "ls";
	toto[1] = 0;
	int forke;

	forke = fork();
	if (forke == 0)
		execve("/usr/bin/ls", toto, env);	
	else
		wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	struct sigaction sa;
	sa.sa_handler = handler;
	t_g *v;

	(void)av;
	if (!env[0])
		ft_error(1);
	if (ac != 1)
		ft_error(2);
	v = malloc(sizeof(t_g));
	if (!v)
		ft_error(2);
	v->env = env;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		str = readline("\033[34m➜\033[0m ");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
		{
			rl_clear_history();
			ft_exit(str);
		}
		if (str[0])
			add_history(str);
		if (str[0])
			parsing(str, v);
		/*if (ft_strncmp(str, "ls", 2) == 0)
			exec_ls(env);
		if (ft_strncmp(str, "pwd", 3) == 0)
			ft_pwd();
		if (ft_strncmp(str, "cd", 2) == 0)
			ft_cd(str + 3);
		*/free(str);
	}
	return (0);
}
