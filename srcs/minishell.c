/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/04 16:32:01 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void s_handler(int sig)
{
	(void)sig;
}


void	handler(int signum)
{
	(void)signum;
	if (SIGINT == 2)
		write(0, "\n\033[34m➜\033[0m ", 15);
	else
		return ;
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
		signal(SIGINT, handler);
		//sigaction(SIGINT, &sa, NULL);
		str = readline("\033[34m➜\033[0m ");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
		{
			rl_clear_history();
			ft_exit(str);
		}
		if (str[0])
			add_history(str);
		if (str[0])
		{
			parsing(str, env);
		}
		free(str);
	}
	return (0);
}
