/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/04/05 14:19:00 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	(void)av;
	if (ac != 1)
		ft_error(2);
	while (1)
	{
		signal(SIGINT, handler);
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
