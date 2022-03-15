/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:40:12 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/15 16:53:30 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	if (!env[0])
		ft_error(1);
	if (ac != 1)
		ft_error(2);
	ft_putstr_fd("➜ ", 1);
	str = get_next_line(0);
	while (str && ft_strncmp(str, "exit\n", 6) != 0)
	{
		ft_putstr_fd("➜ ", 1);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(42);
	ft_putstr_fd("Bye 👋\n", 1);
	return (0);
}
