/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:54:04 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/07 20:54:07 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name(char *str)
{
	int		count;
	int		space;
	char	*string;

	count = 0;
	space = 0;
	while (str[count] == ' ')
		space++;
	while (str[space + count] && str[space + count] != ' ')
		count++;
	string = malloc((count + 1) * sizeof(char));
	count = 0;
	while (str[space + count] && str[space + count] != ' ')
	{
		string[count] = str[space + count];
		count++;
	}	
	string[count] = '\0';
	return (string);
}

void	executable(char *prompt, int fd)
{
	int status;
	char *args[2];

	(void)fd;
	args[0] = ft_strjoin("/bin/", name(prompt));
	args[1] = NULL;
	if (fork() == 0)
		execv(args[0], args);
	else
		wait(&status);
	free(args[0]);
}
/*int main( void )
{
	int status;
	char *args[2];

	args[0] = "/bin/ls";        // first arg is the full path to the executable
	args[1] = NULL;             // list of args must be NULL terminated
	if ( fork() == 0 )
		execv( args[0], args ); // child: call execv with the path and the args
	else
		wait( &status );        // parent: wait for the child (not really necessary)
	return 0;
}*/