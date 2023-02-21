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
		return (firststop + count2 + 1);
	}
	return (firststop + 1);
}

void	ft_printenv(char *str, int fd)
{
	int	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == '=')
		{
			count++;
			break ;
		}
		count++;
	}
	while (str[count])
	{
		ft_putchar_fd(str[count], fd);
		count++;
	}
}

int	dollarsign(char *str, int c, t_prompt *every)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str[count] == '?')
		ft_printf(every->fd, "%d", every->exit_stat);
	while (str[count] && str[count] != ' ')
		count++;
	while (every->new_env[i])
	{
		if (!ft_strncmp(str, every->new_env[i], count))
		{
			ft_printenv( every->new_env[i], every->fd);
			break ;
		}
		i++;
	}
	return (count + c + 1);
}
/*int	does_it_have_2doublequotes(char *str, int firststop, int fd)
{
	int count;
	int	count2;
	int	flag;

	count2 = 0;
	flag = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == '"')
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
			if (s[c] == '$')
				c = dollarsign(s + c + 1, c, fd);
			if (str[count] != '"')
				ft_putchar_fd(str[count], fd);
			count++;
		}
		return (firststop + count2 + 1);
	}
	return (firststop + 1);
}
*/

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
		//if (s[c] == '"')
		//	c = does_it_have_2doublequotes(s + c, c, fd);
		if (s[c] == '$')
			c = dollarsign(s + c + 1, c, every);
		if (s[c] == '>' || s[c] == '<' || s[c] == '|')
			break ;
		if (flag == 1 && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		{
			ft_putchar_fd(' ', every->fd);
			flag = 0;
		}
		if (s[c] != ' ' && s[c] != '\t' && s[c] != '\n')
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
