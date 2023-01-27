/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:22:56 by fvieira           #+#    #+#             */
/*   Updated: 2023/01/23 17:22:57 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void ls(char *argv) 
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (argv)) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	  	if(ent->d_name[0] != '.')
	   	 printf ("%s   ", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  perror ("");
	}
	
}*/

void	echo(char *str)
{
	int	count;
	int	flag;

	count = 4;
	flag = 0;
	while (str[count] == ' ' || (str[count] >= 9 && str[count] <= 13))
		count++;
	if(!ft_strncmp(str + count, "-n", 2))
	{
		count += 2;
		flag = 1;
	}
	while (str[count] == ' ' || (str[count] >= 9 && str[count] <= 13))
		count++;
	while (str[count])
	{
		ft_putchar_fd(str[count], 1);
		count++;
	}
	if (flag != 1)
		ft_putchar_fd('\n', 1);
}

void	path(char *path)
{
	char	pwd[1000];

	if (!ft_strncmp(path, "pwd", 3))
		printf("%s\n", getcwd(pwd, 100));
	if (!ft_strncmp(path, "cd", 2))
	{
		if (!ft_strncmp(&path[2], " ..", 3))
			chdir("..");
	}
	if (!ft_strncmp(path, "echo ", 5))
	{
		echo(path);
	}	
}

void handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}

int	main(void)
{
	char 			*line;

	if (signal(SIGINT, handle_signals) == SIG_ERR)
	{
		printf("failed to register interrupts with kernel\n");
	}
	while ((line = readline("prompt% ")))
	{
		if (!ft_strncmp (line, "exit", 4))
		{
			free (line);
			break;
		}
		add_history (line);
		path(line);
		free (line);
	}
	return (0);
}
