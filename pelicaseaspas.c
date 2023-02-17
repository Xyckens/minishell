/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pelicaseaspas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:29:10 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/17 22:04:19 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pelicas_em_aspas(const char *str, int pos)
{
	int c_aspas;
	int	i;

	i = 0;
	c_aspas = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] == '"')
			c_aspas++;
		i++;
	}
	if (c_aspas % 2 == 1)
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (0);
			i++;
		}
	}
	return (1);
}

int	pelicas(const char *str, int pos)
{
	int c_aspas;
	int	i;

	i = 0;
	c_aspas = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == 39)
		{
			if (pelicas_em_aspas(str, i) == 1)
				c_aspas++;
		}
		i++;
	}
	if (c_aspas % 2 == 1)
	{
		while (str[i++])
		{
			if (str[i] == 39)
			{
				if (pelicas_em_aspas(str, i) == 1)
					return (0);
			}
		}
	}
	return (1);
}

int	aspas_em_pelicas(const char *str, int pos)
{
	int c_aspas;
	int	i;

	i = 0;
	c_aspas = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] == 39)
			c_aspas++;
		i++;
	}
	if (c_aspas % 2 == 1)
	{
		while (str[i])
		{
			if (str[i] == 39)
				return (0);
			i++;
		}
	}
	return (1);
}

int	aspas(const char *str, int pos)
{
	int c_aspas;
	int	i;

	i = 0;
	c_aspas = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == '"')
		{
			if (aspas_em_pelicas(str, i) == 1)
				c_aspas++;
		}
		i++;
	}
	if (c_aspas % 2 == 1)
	{
		while (str[i++])
		{
			if (str[i] == '"')
			{
				if (aspas_em_pelicas(str, i) == 1)
					return (0);
			}
		}
	}
	return (1);
}
int	between(const char *str, int pos)
{
	if (pelicas(str, pos) == 1
		&& aspas(str, pos) == 1)
		return (1);
	return (0);
}
