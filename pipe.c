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

void	run_pipe(t_prompt *everything, int *pfd, int c);

/*void	pipes(t_prompt *every, int c)
{
	// int pid;
	// int	status;
	int fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error");
		exit(1);
	}
	else
		wait(NULL);
	run_pipe(every, fd, c);
}*/

void	child(t_prompt *every, int pfd[2], int c)
{
	char	**seperated;

	seperated = initialize(every, c);	
	close(every->fd);
	dup(pfd[1]);
	close(pfd[0]);
	close(pfd[1]);
	idk(seperated[0], seperated, every, c);
	freesplit(seperated);
}

void	parent(t_prompt *every, int pfd[2], int c)
{
	char	**seperated;

	seperated = initialize(every, c);
	close(STDIN_FILENO);
	dup(pfd[0]);
	close(pfd[1]);
	close(pfd[0]);
	idk(seperated[0], seperated, every, c);
	freesplit(seperated);
}

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
}
