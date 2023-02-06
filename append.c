/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:35:05 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/03 19:36:58 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name(char *str)
{
	int		count;
	int		space;
	char	*string;

	count = 0;
	space = 0;
	while (str[count] == ' ')
		space++;
	while (str[space + count] && str[space + count] != ' ')
		count++;
	string = malloc((count + 1) * sizeof(char));
	count = 0;
	while (str[space + count] && str[space + count] != ' ')
	{
		string[count] = str[space + count];
		count++;
	}	
	string[count] = '\0';
	return (string);
}

int	append(char *prompt, int midle)
{
	int		fd;
	char	*path;

	path = name(prompt + midle + 2);
	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0777);
	return (fd);
}
int	redirectout(char *prompt, int midle)
{
	int		fd;
	char	*path;

	path = name(prompt + midle + 2);
	fd = open(path, O_WRONLY | O_CREAT, 0666);
	return (fd);
}