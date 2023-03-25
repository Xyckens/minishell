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

	count2 = 0;
	flag = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == 39)
			flag++;
		if (flag == 2)
		{
			count2 = count;
			break ;
		}
		count++;
	}
	if (flag == 2)
	{
		count = 0;
		while (str[count] && count < count2)
		{
			if (str[count] != 39)
				ft_putchar_fd(str[count], fd);
			count++;
		}
		return (firststop + count2);
	}
	return (firststop);
}

int	does_it_have_2doublequotes(char *s, int firststop, t_prompt *every)
{
	int	count;
	int	count2;
	int	flag;

	count2 = 0;
	flag = 0;
	count = 0;
	while (s[count])
	{
		if (s[count] == '"')
			flag++;
		if (flag == 2)
		{
			count2 = count;
			break ;
		}
		count++;
	}
	if (flag == 2)
	{
		count = 0;
		while (s[count] && count < count2)
		{
			if (s[count] != '"')
				ft_putchar_fd(s[count], every->fd);
			count++;
		}
		return (firststop + count2);
	}
	return (firststop);
}


void	ft_epur(char *s, t_prompt *every)
{
	int	c;
	int	flag;
	int	l;

	c = 0;
	flag = 0;
	l = ft_strlen(s) - 1;
	while (s[c] != '\0' && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		c++;
	while (l > 0 && (s[l] == ' ' || s[l] == '\t' || s[l] == '\n'))
		l--;
	while (c <= l)
	{
		if (s[c] == 39)
			c = does_it_have_2quotes(s + c, c, every->fd);
		else if (s[c] == '"')
			c = does_it_have_2doublequotes(s + c, c, every);
		else if (flag == 1 && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		{
			ft_putchar_fd(' ', every->fd);
			flag = 0;
		}
		else if (s[c] != ' ' && s[c] != '\t' && s[c] != '\n')
		{
			flag = 1;
			ft_putchar_fd(s[c], every->fd);
		}
		c++;
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
