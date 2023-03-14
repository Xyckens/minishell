/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:59:34 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/07 17:15:02 by fvieira          ###   ########.fr       */
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

int	next(char **sep, int *order, int pos, int jump)
{
	int	c;

	c = 0;
	if (pos == -1)
	{
		if (!sep[c])
			return (c);
		while (sep[c])
		{
			if (order[c] == 0)
				return (c);
			c++;
		}	
	}
	while (sep[c])
	{
		if (order[c] == order[pos] + jump)
			return (c);
		c++;
	}
	printf("c = %i, jump = %i order = %i\n", c, jump, order[pos]);
	return (c + 1);
}

int	use_last(t_prompt *eve, int f)
{
	int	i;

	i = f;
	while (eve->sep[i] && eve->sep[i][0] == eve->sep[f][0])
	{
		if (eve->sep[i][0] != '|' && eve->fd != 1)
			close(eve->fd);
		if (eve->sep[i][0] == '>' && eve->sep[i][1] != '>')
			eve->fd = redirectout(eve->cmd[i + 1]);
		if (eve->sep[i][0] == '>' && eve->sep[i][1] == '>')
			eve->fd = append(eve->cmd[i + 1]);
		if (eve->sep[i][0] == '<' && eve->sep[i][1] != '<')
			eve->fd = redirectin(eve->cmd[i + 1]);
		//if (eve->sep[i][0] == '<' && eve->sep[i][1] == '<')
		i++;
	}
	if (eve->sep[f][0] == '|' && i > f + 1)
		mult_pipes(eve, f, i - f);
	return (i - f);
}

int	parser(t_prompt *eve)
{
	int	ex;
	int	jump;

	ex = next(eve->sep, eve->order, -1, 1);
	eve->fd = 1;
	while (eve->cmd[ex])
	{
		printf("\n \nsep %s cmd %s\n \n", eve->sep[ex], eve->cmd[ex]);
		jump = 1;
		if (eve->sep[ex])
		{
			if (eve->sep[ex][0] == '|')
			{
				printf("pipes?\n");
				//pipes(eve, ex);
			}
		// if (eve->sep[ex] == '<' && eve->sep[ex + 1] == '<')
		// 		delimiter(eve->sep, c++);
			if (eve->sep[ex][0] == '>' || eve->sep[ex][0] == '<' || eve->sep[ex][0] == '|')
				jump = use_last(eve, ex);
		}
		if (ex >= 1)
		{
			if (eve->sep[ex - 1][0] != '|')
				path(eve, ex);
		}
		else if (!eve->sep[ex] || eve->sep[ex][0] != '|')
			path(eve, ex);
		ex = next(eve->sep, eve->order, ex, jump);
	}
	if (eve->fd != 1)
		close(eve->fd);
	return (1);
}
