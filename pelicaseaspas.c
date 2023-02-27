/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pelicaseaspas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:29:10 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/27 21:56:32 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sep_init(t_prompt *e)
{
	char	**sep;
	int		i;
	int		c;
	int		j;

	i = 2;
	c = 0;
	j = 0;
	sep = malloc((count_words(e->prompt, "><|")) * sizeof(char *));
	while (e->prompt[c])
	{
		if ((e->prompt[c] == '>' || e->prompt[c] == '<' || e->prompt[c] == '|') && between(e->prompt, c) == 1)
		{
			if (e->prompt[c + 1] == '>' || e->prompt[c + 1] == '<')
				i++;
			sep[j] = malloc(i);
			sep[j][0] = e->prompt[c];
			sep[j][i - 1] = '\0';
			if (e->prompt[c + 1] == '>' || e->prompt[c + 1] == '<')
				sep[j][1] = e->prompt[++c];
			j++;
		}
		c++;
	}
	sep[j] = 0;
	return (sep);
}

int	between(const char *str, int pos)
{
	int	temp;
	int	flag;
	int	c;

	temp = -1;
	flag = 1;
	c = -1;
	while (str[++c] && c <= pos)
	{
		if (temp >= 0 && str[c] == str[temp])
		{
			temp = -1;
			flag = 1;
			continue ;
		}
		if ((str[c] == 39 || str[c] == '"') && temp == -1)
		{
			temp = c;
			flag = 0;
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	correctorder(char **sep, int i)
{
	int	c;
	int	counter;

	c = 0;
	counter = 0;
	while (sep[c])
	{
		if (sep[i][0] > sep[c][0])
			counter++;
		if (sep[i][0] == sep[c][0] && i > c)
			counter++;
		c++;
	}
	return (counter);
}

int	*order(t_prompt *every)
{
	int	*order;
	int	i;
	int	count;

	count = (count_words(every->prompt, "><|"));
	order = malloc(count * sizeof(int *));
	i = 0;
	while (i < count - 1)
	{
		order[i] = correctorder(every->sep, i);
		i++;
	}
	return (order);
}