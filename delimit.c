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

/*char	*redirectin(char *prompt)
{
	char	*line;
	char	*content;
	int		fd;

	fd = open(prompt, O_RDONLY);
	content = "\0";
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		content = ft_strjoin(content, line);
		free(line);
	}
	free(content);
	close(fd);
	return (prompt);
}*/

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