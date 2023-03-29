/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:55:34 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/11 15:55:35 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirectin(char	*name)
{
	int		fd;

	fd = open(name, O_RDONLY | O_CLOEXEC, 0666);
	if (fd == -1)
	{
		printf("prompt: no such file or directory: gfd\n");
		exit(127);
	}
	return (fd);
}

int	hereindoc(t_prompt *every)
{
	char	*buff;
	int		fd;

	buff = "\0";
	fd = open("libft/.test.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
	while (1)
	{
		every->prompt = readline("> ");
		if (ft_strcmp(every->prompt, every->cmd[1]))
		{
			ft_printf(fd, every->prompt);
			ft_printf(fd, "\n");
		}
		else
			break ;
		free (every->prompt);
	}
	every->herein = 0;
	every->clean = 1;
	every->parser = 1;
	return (redirectin("libft/.test.txt"));
}
