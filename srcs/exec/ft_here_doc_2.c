/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:39:38 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/05 13:41:36 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_str_null(void)
{
	printf("\n");
	printf("minishell: warning: here-document at line 1");
	printf("delimited byend-of-file (wanted `%s')\n", g_shell.test);
	free(g_shell.test);
	exit(0);
}

void	ft_error_limiter(char *str)
{
	free(str);
	free(g_shell.test);
	exit(0);
}

void	ft_value_is_2(t_l *tmp)
{
	if (tmp->name_in)
	{
		close(tmp->in);
		unlink(tmp->name_in);
	}
	g_shell.retour = 130;
	printf("\n");
}

void	handler2(int signum)
{
	if (signum == 3 && g_shell.in_exec == 1)
	{
		write (2, "lol\n", 4);
		g_shell.retour = 131;
	}
	if (signum == 2)
	{
		g_shell.retour = 130;
		free(g_shell.test);
		exit(2);
	}
	else
		return ;
}

int	create_tmp_file(t_l *tmp)
{
	int		dev;
	char	random[11];
	int		i;

	i = 0;
	dev = open("/dev/urandom", O_RDONLY);
	if (dev == -1)
		return (ft_custom_error("open error in create_tmp_file()\n", 0, NULL));
	read(dev, random, 10);
	close(dev);
	random[10] = 0;
	while (random[i])
	{
		if (random[i] == '/')
			random[i] = 123;
		i++;
	}
	close(dev);
	tmp->name_in = ft_strjoin(".tmp_file", random);
	if (!tmp->name_in)
		return (ft_custom_error("strjoin error in create_tmp_file()\n",
				0, NULL));
	return (1);
}
