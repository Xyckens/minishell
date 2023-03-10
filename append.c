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

int	append(char *prompt)
{
	int		fd;

	fd = open(prompt, O_CREAT | O_RDWR | O_APPEND, 0666);
	return (fd);
}

int	redirectout(char *prompt)
{
	int		fd;

	fd = open(prompt, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}
