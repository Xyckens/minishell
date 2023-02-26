/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:59:34 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/02 21:54:16 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_removeenv(char **new_env, int pos)
{
	int		count;

	count = pos;
	while (new_env[count + 1])
	{
		new_env[count] = new_env[count + 1];
		count++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void	several_unset(char *st_arg, t_prompt *every)
{
	char	**toremove;
	int		count;
	int		i;

	count = 0;
	toremove = ft_split(st_arg, ' ');
	while (toremove[count])
		count++;
	while (--count >= 0)
	{
		i = -1;
		while (every->new_env[++i])
		{
			if (!ft_strncmp(toremove[count], every->new_env[i], ft_strlen(toremove[count])))
			{
				every->new_env = ft_removeenv(every->new_env, i);
				break ;
			}
		}
	}
	freesplit(toremove);
}

char	**ft_unset(t_prompt *every, int c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (!every->st_arg[c])
	{
		ft_printf(2, "unset: not enough arguments\n");
		every->exit_stat = 1;
	}
	else
	{
		several_unset(every->st_arg[c], every);
		every->exit_stat = 0;
	}
	return (every->new_env);
}

void	path(t_prompt *every, int c)
{
	char	pwd[1000];

	if (!ft_strcmp(every->cmd[c], "pwd"))
	{
		ft_printf(every->fd, "%s\n", getcwd(pwd, 100));
		every->exit_stat = 0;
	}
	else if (!ft_strcmp(every->cmd[c], "cd"))
		change_directory(every, pwd);
	else if (!ft_strcmp(every->cmd[c], "echo"))
		echo(every, c);
	else if (!ft_strcmp(every->cmd[c], "export"))
		every->new_env = ft_export(every, c);
	else if (!ft_strcmp(every->cmd[c], "unset"))
		every->new_env = ft_unset(every, c);
	else if (!ft_strcmp(every->cmd[c], "exit"))
	{
		ft_printf(1, "exit: too many arguments\n");
		every->exit_stat = 1;
	}
	else
		executable(every, c);
}

int	parser(t_prompt *eve)
{
	int	c;

	c = 0;
	eve->fd = 1;
	while (eve->cmd[c])
	{
		//if (eve->sep[c] == '|')
		//	pipes(eve, c);
		// if (eve->sep[c] == '<' && eve->sep[c + 1] == '<')
		// 		delimiter(eve->sep, c++);
		// if (eve->sep[c][0] == '<' && eve->sep[c][1] != '<')
		// 	eve->prompt = redirectin(eve->cmd[1]);
		if (eve->sep[c] && eve->sep[c][0] == '>' && eve->sep[c][1] == '>')
			eve->fd = append(eve->cmd[c + 1]);
		else if (eve->sep[c] && eve->sep[c][0] == '>' && eve->sep[c][1] != '>')
			eve->fd = redirectout(eve->cmd[c + 1]);
		if (c == 0 || (eve->sep[c - 1][0] != '>' && eve->sep[c - 1][0] != '<' ))
			path(eve, c);
		if (eve->fd != 1)
			close(eve->fd);
		eve->fd = 1;
		c++;
	}
	return (eve->fd);
}
