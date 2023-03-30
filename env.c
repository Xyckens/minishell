/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegger-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:24:26 by jegger-s          #+#    #+#             */
/*   Updated: 2023/03/03 20:24:28 by jegger-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_prompt *every, int c)
{
	int	i;

	i = 0;
	while (every->new_env[i])
	{
		c = -1;
		while (every->new_env[i][++c])
			ft_putchar_fd(every->new_env[i][c], every->fd);
		ft_putchar_fd('\n', every->fd);
		i++;
	}
	every->exit_stat = 0;
}
