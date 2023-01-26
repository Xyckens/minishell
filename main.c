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

void ls(char *argv) 
{ 
	struct dirent **namelist;
	int n;

	n = scandir(argv, &namelist, NULL, NULL);
	if(n < 0)
	{
		perror("scandir");
		//exit(EXIT_FAILURE);
	}
	else
	{
		alphabeticsort(namelist);
		while (n-- > 2)
		{
			if(namelist[n]->d_name[0] != '.')
				printf("%s  ",namelist[n]->d_name);
			free(namelist[n]);
		}
		free(namelist);
		printf("\n");
	}
	//exit(EXIT_SUCCESS);
}

void	path(char *path)
{
	char	pwd[1000];
	char *s;

	if (!ft_strncmp(path, "pwd", 3))
		printf("%s\n", getcwd(pwd, 100));
	if (!ft_strncmp(path, "cd", 2))
	{
		if (!ft_strncmp(&path[2], " ..", 3))
			chdir("..");
	}
	if (!ft_strncmp(path, "ls", 2))
	{
		s = getcwd(pwd, 100);
		ls(s);
	}
}
int	main(void)
{
	//DIR	*dir;
	char 			*line;
	while (1)
	{
		line = readline("prompt% ");
		path(line);
	}
	return (0);
}
/*#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

void traverse(char *fn, int indent) {
  DIR *dir;
  struct dirent *entry;
  int count;
  char path[1025];
  struct stat info;

  for (count=0; count<indent; count++) printf("  ");
  printf("%s\n", fn);

  if ((dir = opendir(fn)) == NULL)
    perror("opendir() error");
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_name[0] != '.') {
        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path,
                  strerror(errno));
        else if (S_ISDIR(info.st_mode))
               traverse(path, indent + 1);
      }
    }
    closedir(dir);
  }
}

int main(void) {
  puts("Directory structure:");
  traverse("/etc", 0);
}*/

