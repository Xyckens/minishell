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

void	whatamidoing(t_prompt *env, int c)
{
	(void)env;
	// int pid;
	// int	status;
	int fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error");
		exit(1);
	}

	// Provavelmente nao vamos usar

	// pid = fork();
	// if (pid > 0)
	// {
	// 	while ((pid = wait(&status)) != -1)
	// 		fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
	// }
	// else if (pid == 0)
	// {
	// 	run_pipe(env, fd, c);
	// 	exit(0);
	// }

	run_pipe(env, fd, c);
}

void	run_pipe(t_prompt *everything, int *pfd, int c)
{
	int pid;

	pid = fork();
	if (pid == 0)/* child */
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		// printf("Child RunPipe: %s - C: %d\n", everything->cmd[c], c);
		// printf("            CHILD          \n");
		executable(everything, c);
		// wait(NULL);
		close(pfd[1]);
		exit(0);
	}
	if (pid > 0) /* parent */
	{
		c++;
		// printf("Parent RunPipe: %s - C: %d\n", everything->cmd[c], c);
		dup2(pfd[0], 0);
		close(pfd[1]);
		printf("            PARENT          \n");
		executable(everything, c);
	}	
}

// void	whatamidoing(t_prompt *env)
// {
// 	pid_t	pid;
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 	{
// 		printf("Error");
// 		exit(1);
// 	}
// 	pid = fork(); 
// 	if (pid > 0)
// 	{
// 		close(fd[0]);
// 		// int		fd_file;
// 		// char	buff[100];
// 		// fd_file = open(env->st_arg[0], O_RDONLY);
// 		// read(fd_file, buff, 1000);
// 		// dup2(env->fd, fd[1]);
// 		// write(fd[1], buff, sizeof(buff) + 1);
// 		// wait(NULL);
// 	}
// 	else if (pid == 0)
// 	{
// 		// char str_recebida[200];
// 		close(fd[1]);
// 		dup2(env->fd, fd[1]);
// 		// read(fd[0], str_recebida, sizeof(str_recebida));
// 		// printf("ELSE:\n%s\n", str_recebida);
// 		// env->cmd[0] = "sort";
// 		// close(fd[0]);
// 	}
// 	else
// 		exit(1);
// }