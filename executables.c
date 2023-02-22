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

void	idk(char **args, t_prompt *everything)
{
	dup2(everything->fd, 1);
	if (execve(args[0], args, everything->new_env) == -1)
		args[0] = ft_strjoin("/bin/", args[0]);
	if (execve(args[0], args, everything->new_env) == -1)
	{
		ft_printf(2, "%s: command not found\n", args[0] + 5);
		everything->exit_stat = 127;
	}
	else
		everything->exit_stat = 0;
	//nao gosto como isto ficou
	//mas da tua maneira tb nao podia ser
	//alterei para ser no fd 2 o stderr
}

void	executable(t_prompt *everything, int c)
{
	int		status;
	char	**nome;

	nome = initialize(everything, c);
	if (fork() == 0)
		idk(nome, everything);
	else
		wait(&status);
	//vai ser preciso dar free a todos os elementos do nome
	//por causa do split
	free(nome);
}
