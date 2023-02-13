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

char	*redirectin(char *prompt, int middle)
{
	char	*path;
	char	*line;
	char	*content;
	int		fd;

	path = name(prompt + middle + 2);
	fd = open(path, O_RDONLY);
	line = "oi";
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
	prompt = ft_strjoin(ft_substr(prompt, 0, middle), content);
	free(content);
	close(fd);
	return (prompt);
}