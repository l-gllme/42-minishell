/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:17:13 by lguillau          #+#    #+#             */
/*   Updated: 2022/03/16 14:24:29 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	free(str);
}
