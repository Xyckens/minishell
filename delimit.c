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