/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/16 14:00:37 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void exec_cat(char **env)
{
	char **toto;
	toto = malloc(sizeof(char *) * 3);
	toto[0] = "ls";
	toto[1] = "-l";
	toto[2] = 0;
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

	(void)av;
	if (!env[0])
		ft_error(1);
	if (ac != 1)
		ft_error(2);
	ft_putstr_fd("\033[36m➜\033[0m ", 1);
	str = get_next_line(0);
	while (str && ft_strncmp(str, "exit\n", 6) != 0)
	{
		if (ft_strncmp(str, "ls -l\n", 6) == 0)
			exec_cat(env);
		ft_putstr_fd("\033[36m➜\033[0m ", 1);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(42);
	ft_putstr_fd("Bye! 👋\n", 1);
	return (0);
}
