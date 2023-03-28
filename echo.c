/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:34:26 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/11 18:34:30 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	does_it_have_2quotes(char *str, int firststop, int fd)
{
	int	count;
	int	count2;
	int	flag;

	flag = 0;
	count = -1;
	while (str[++count])
	{
		if (str[count] == str[0])
			flag++;
		if (flag == 2)
		{
			count2 = count;
			break ;
		}
	}
	if (flag == 2)
	{
		count = -1;
		while (str[++count] && count < count2)
			if (str[count] != str[0])
				ft_putchar_fd(str[count], fd);
		return (firststop + count2);
	}
	return (firststop);
}

int	does_it_have_2doublequotes(char *s, int firststop, t_prompt *every)
{
	int	count;
	int	count2;
	int	flag;

	flag = 0;
	count = -1;
	while (s[++count])
	{
		if (s[count] == '"')
			flag++;
		if (flag == 2)
		{
			count2 = count;
			break ;
		}
	}
	if (flag == 2)
	{
		count = -1;
		while (s[++count] && count < count2)
			if (s[count] != '"')
				ft_putchar_fd(s[count], every->fd);
		return (firststop + count2);
	}
	return (firststop);
}

void	ft_epur(char *s, t_prompt *every)
{
	int	c;
	int	flag;

	c = -1;
	flag = 0;
	while (s[c + 1] != '\0' && (s[c + 1] <= ' '))
		c++;
	while (s[++c])
	{
		if (s[c] == 39 || s[c] == '"')
			c = does_it_have_2quotes(s + c, c, every->fd);
		else if (flag == 1 && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		{
			flag = 0;
			ft_putchar_fd(s[c], every->fd);
			while (s[c + 1] && (s[c + 1] <= ' '))
				c++;
		}
		else if (s[c] != ' ' && s[c] != '\t' && s[c] != '\n')
		{
			flag = 1;
			ft_putchar_fd(s[c], every->fd);
		}
	}
}

void	echo(t_prompt *every, int c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (every->st_arg[c][count] == ' '
		|| (every->st_arg[c][count] >= 9 && every->st_arg[c][count] <= 13))
		count++;
	if (!ft_strncmp(every->st_arg[c] + count, "-n", 2))
	{
		count += 2;
		flag = 1;
	}
	while (every->st_arg[c][count] == ' '
		|| (every->st_arg[c][count] >= 9 && every->st_arg[c][count] <= 13))
		count++;
	ft_epur(every->st_arg[c] + count, every);
	if (flag != 1)
		ft_putchar_fd('\n', every->fd);
	every->exit_stat = 0;
}
