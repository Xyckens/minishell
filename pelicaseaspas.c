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

int	between(const char *str, int pos)
{
	int	temp;
	int	flag;
	int	c;

	temp = -1;
	flag = 1;
	c = 0;
	//printf("char = %c %d\n",str[pos], pos);
	while (str[c] && c <= pos)
	{
		//printf("temp%d\n", temp);
		if (temp >= 0 && str[c] == str[temp])
		{
			temp = -1;
			flag = 1;
			c++;
			continue ;
		}
		if ((str[c] == 39 || str[c] == '"') && temp == -1)
		{
			temp = c;
			flag = 0;
		}
		//printf("\nflag = %d char = %c to compare %c\n", flag, str[c], str[temp]);
		c++;
	}
	//printf("ola %c %d\n", str[pos], flag);
	if (flag == 1)
		return (1);
	return (0);
}
