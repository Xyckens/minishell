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
		//printf("pfd%d\n", pfd[i]);
		close(pfd[i]);
		i++;
	}
}
void	child(t_prompt *every, int *pfd, int mult, int c)
{
	char	**seperated;

	printf("child %d %d \n",pfd[0], pfd[1] );
	printf("cmd %s\n",every->cmd[c]);
	seperated = initialize(every, c);
	close(every->fd);
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
		printf("error\n");
	closefd(pfd, mult);
	idk(seperated[0], seperated, every, c);
	freesplit(seperated);
}

void	alt_child(t_prompt *every, int *pfd, int i, int mult, int c)
{
	char	**seperated;

	printf("alt_child  old %d %d \n", pfd[i - 2], pfd[i - 1]);	
	printf("alt_child  new %d %d \n", pfd[i], pfd[i + 1]);
	printf("cmd %s\n",every->cmd[c]);
	seperated = initialize(every, c);
	dup2(pfd[i + 1], STDOUT_FILENO);
	if (dup2(pfd[i - 2], STDIN_FILENO) < 0)
		printf("ERROR\n");
	closefd(pfd, mult);
	idk(seperated[0], seperated, every, c);
	freesplit(seperated);
}

void	parent(t_prompt *every, int *pfd, int i, int mult, int c)
{
	char	**seperated;

	printf("parent %d %d \n",pfd[i - 2], pfd[i - 1]);
	printf("cmd %s\n",every->cmd[c]);
	seperated = initialize(every, c);
	close(STDIN_FILENO);
	if (dup(pfd[i - 2]) < 0)
		printf("error\n");
	closefd(pfd, mult);
	idk(seperated[0], seperated, every, c);
	freesplit(seperated);
}

void	mult_pipes(t_prompt *every, int c, int mult)
{
	pid_t pid;
	int	status;
	int pfd[(mult - 1) * 2];
	int	i;

	i = 0;
	printf("mult %d\n", mult);
	while (i < mult - 1)
	{
		if (pipe(pfd + i * 2) == -1)
		{
			printf("Error");
			exit(1);
		}
		i++;
	}
	pid = fork();
	if (pid == 0)
		child(every, pfd, mult, c);
	c++;
	//waitpid(pid, &status, 0);
	//every->exit_stat = status >> 8;
	i = 1;
	while (mult > 1 && every->sep[c] && every->sep[c][0] == '|')
	{
		//printf("loop cmd %s\n", every->cmd[c]);
		pid = fork();
		if (pid == 0)
			alt_child(every, pfd, i + 1, mult,  c);
		i += 2;
		c++;
		// waitpid(pid, &status, 0);
		//every->exit_stat = status >> 8;
		//printf("ola \n");

	}
	/*int o;
	o = 0;
	while (o < mult)
	{
		//printf("pfd%d\n", pfd[o]);
		waitpid(-1, &status, 0);
		every->exit_stat = status >> 8;
		o++;
	}*/
	pid = fork();
	if (pid == 0)
		parent(every, pfd, i + 1, mult, c);
	closefd(pfd, mult);
	waitpid(pid, &status, 0);
	every->exit_stat = status >> 8;

}
/*
void	pipes(t_prompt *everything, int c)
{
	pid_t pid;
	int	status;
	int pfd[2];

	if (pipe(pfd) == -1)
	{
		printf("Error");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
		child(everything, pfd, c);
	waitpid(pid, &status, 0);
	everything->exit_stat = status >> 8;
	pid = fork();
	if (pid == 0)
		parent(everything, pfd, c + 1);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	everything->exit_stat = status >> 8;
}*/
