/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:31:47 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/16 18:31:48 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefd(int *pfd, int mult)
{
	int	i;

	i = 0;
	while (i < mult * 2 - 2)
	{
		close(pfd[i]);
		i++;
	}
}

void	child(t_prompt *every, int *pfd, int mult, int c)
{
	close(every->fd);
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
		printf("error\n");
	closefd(pfd, mult);
	path(every, c);
	exit(every->exit_stat);
}

void	alt_child(t_prompt *every, int *pfd, int i, int mult, int c)
{
	dup2(pfd[i + 1], STDOUT_FILENO);
	if (dup2(pfd[i - 2], STDIN_FILENO) < 0)
		printf("ERROR\n");
	closefd(pfd, mult);
	path(every, c);
	exit(every->exit_stat);
}

void	parent(t_prompt *every, int *pfd, int i, int mult, int c)
{
	close(STDIN_FILENO);
	if (dup(pfd[i - 2]) < 0)
		printf("error\n");
	closefd(pfd, mult);
	path(every, c);
	exit(every->exit_stat);
}

void	mult_pipes(t_prompt *every, int c, int mult)
{
	pid_t	pid;
	int		status;
	int 	pfd[(mult - 1) * 2];
	int		i;

	i = 0;
	while (i < mult - 1)
	{
		if (pipe(pfd + i * 2) == -1)
			exit(1);
		i++;
	}
	pid = fork();
	if (pid == 0)
		child(every, pfd, mult, c);
	c++;
	i = 1;
	while (mult > 1 && every->sep[c] && every->sep[c][0] == '|')
	{
		pid = fork();
		if (pid == 0)
			alt_child(every, pfd, i + 1, mult, c);
		i += 2;
		c++;
	}
	pid = fork();
	if (pid == 0)
		parent(every, pfd, i + 1, mult, c);
	closefd(pfd, mult);
	i = 0;
	while (i < mult)
	{
		waitpid(-1, &status, 0);
		every->exit_stat = status >> 8;
		i++;
	}
}
