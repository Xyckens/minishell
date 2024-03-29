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

void	minipath(t_prompt *every)
{
	ft_printf(1, "exit: too many arguments\n");
	every->exit_stat = 1;
}

void	path(t_prompt *every, int c)
{
	char	pwd[1000];

	if (ft_strcmp(every->cmd[c], "echo"))
		every->st_arg[c] = ft_alt_strtrim(every->st_arg[c], "\" \t");
	if (!ft_strcmp(every->cmd[c], "echo"))
		echo(every, c);
	else if (!ft_strcmp(every->cmd[c], "pwd"))
	{
		ft_printf(every->fd, "%s\n", getcwd(pwd, 100));
		every->exit_stat = 0;
	}
	else if (!ft_strcmp(every->cmd[c], "cd"))
		change_directory(every, pwd);
	else if (!ft_strcmp(every->cmd[c], "export"))
		every->new_env = ft_export(every, c);
	else if (!ft_strcmp(every->cmd[c], "unset"))
		every->new_env = ft_unset(every, c);
	else if (!ft_strcmp(every->cmd[c], "exit"))
		minipath(every);
	else if (!ft_strcmp(every->cmd[c], "env"))
		ft_env(every, c);
	else
		executable(every, c);
	unlink("libft/.test.txt");
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
	return (c + 1);
}

int	use_last(t_prompt *eve, int f)
{
	int	i;
	int	mult[2];

	i = f;
	mult[0] = -1;
	while (eve->sep[i] && eve->sep[i][0] == eve->sep[f][0])
	{
		if (eve->sep[i][0] != '|' && eve->fd != 1)
			close(eve->fd);
		if (eve->sep[i][0] == '>' && eve->sep[i][1] != '>')
			eve->fd = redirectout(eve->cmd[i + 1]);
		if (eve->sep[i][0] == '>' && eve->sep[i][1] == '>')
			eve->fd = append(eve->cmd[i + 1]);
		if (eve->sep[i][0] == '<' && eve->sep[i][1] != '<')
			eve->fdinput = redirectin(eve->cmd[i + 1]);
		if (eve->sep[i][0] == '<' && eve->sep[i][1] == '<')
			eve->fdinput = hereindoc(eve);
		i++;
	}
	mult[1] = i - f + 1;
	if (eve->sep[f][0] == '|' && i > f)
		mult_pipes(eve, f, mult);
	return (i - f);
}

int	parser(t_prompt *eve)
{
	int	ex;
	int	jump;

	ex = next(eve->sep, eve->order, -1, 1);
	eve->fd = 1;
	eve->fdinput = -30;
	while (eve->cmd[ex])
	{
		jump = 1;
		if (eve->sep[ex])
			jump = use_last(eve, ex);
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
