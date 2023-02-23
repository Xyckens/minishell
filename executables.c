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
	while (str[space] == ' ')
		space++;
	while (str[space + count] && str[space + count] != '"'
		&& str[space + count] != '>' && str[space + count] != '|'
		&& str[space + count] != 39)
		count++;
	string = malloc((count + 1) * sizeof(char));
	count = 0;
	while (str[space + count] && str[space + count] != '"'
		&& str[space + count] != '>' && str[space + count] != '|'
		&& str[space + count] != 39)
	{
		string[count] = str[space + count];
		count++;
	}	
	string[count] = '\0';
	return (string);
}

char	**initialize(t_prompt *everything, int c)
{
	char	**nome;
	char	**args;
	int		count;

	count = 0;
	args = ft_split(everything->st_arg[c], ' ');
	while (args[count])
		count++;
	nome = malloc((count + 2) * sizeof(char *));
	nome[0] = everything->cmd[c];
	nome[count + 1] = 0;
	count = 0;
	while (args[count])
	{
		nome[count + 1] = args[count];
		count++;
	}
	return (nome);
}

char	**pathfinder(char **new_env)
{
	int		count;
	int		i;
	char	*pathinicial;
	char	**path;

	count = 6;
	i = -1;
	
	while (new_env[++i])
	{
		if (!ft_strncmp("PATH", new_env[i], 4))
		{
			pathinicial = new_env[i] + 5;
			break ;
		}
	}
	path = ft_split(pathinicial, ':');
	return (path);
}

int	idk(char *arg0, char **args, t_prompt *everything)
{
	char	**path;
	int i;

	i = 0;
	path = pathfinder(everything->new_env);
	dup2(everything->fd, 1);
	if (execve(args[0], args, everything->new_env) == -1)
	{
		arg0 = ft_strjoin("/", arg0);
		while (path[i])
		{
			free(args[0]);
			args[0] = ft_strjoin(path[i], arg0);
			if (execve(args[0], args, everything->new_env) == -1)
				i++;
			else
			{
				freesplit(path);
				return (0);
			}
		}
	}
	if (!path[i])
	{
		freesplit(path);
		ft_printf(2, "%s: command not found\n", arg0 + 1);
		free(arg0);
	}
	return (127);
}

void	executable(t_prompt *everything, int c)
{
	int		status;
	char	**seperated;

	seperated = initialize(everything, c);
	if (fork() == 0)
		everything->fd = idk(seperated[0], seperated, everything);
	else
		wait(&status);
	freesplit(seperated);
}
