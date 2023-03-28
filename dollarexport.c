/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarexport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:09:06 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/28 22:09:10 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	between2(const char *str, int pos)
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
		if (str[c] == 39 && temp == -1)
		{
			temp = c;
			flag = 0;
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	count_words2(char const *s, char *c)
{
	int	words;
	int	i;
	int	j;

	words = 1;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (j < 3)
		{	
			if (s[i] == c[j] && i > 0 && s[i - 1] != c[0]
				&& s[i - 1] != c[1] && s[i - 1] != c[2])
			{
				if (between2(s, i) == 1)
				{
					words++;
					break ;
				}
			}
			j++;
		}
		i++;
	}	
	return (words);
}

int	validate_variables(char *str, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			if (flag)
				free(str);
			return (0);
		}
		i++;
	}
	if (flag)
		free(str);
	return (1);
}
