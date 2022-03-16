/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/16 16:47:39 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signum)
{
	(void)signum;
}

static void exec_ls(char **env)
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

	(void)av;
	if (!env[0])
		ft_error(1);
	if (ac != 1)
		ft_error(2);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		toto;
		str = readline("\033[34m➜\033[0m ");
		if (ft_strncmp(str, "exit", 5) == 0)
			ft_exit(str);
		if (ft_strncmp(str, "ls", 2) == 0)
			exec_ls(env);
		if (ft_strncmp(str, "pwd", 3) == 0)
			ft_pwd();
		free(str);
	}
	return (0);
}
