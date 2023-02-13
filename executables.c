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

void	idk(char **args, t_prompt *everything)
{
	dup2(everything->fd, 1);
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

void	executable(char *prompt, t_prompt *everything)
{
	int		status;
	char	**nome;

	nome = ft_split(name(prompt), ' ');
	// a funcao name crasha o programa
	// quando nao se escreve nada e se da enter
	nome[0] = ft_strjoin("/bin/", nome[0]);
	if (fork() == 0)
		idk(nome, everything);
	else
		wait(&status);
	//vai ser preciso dar free a todos os elementos do nome
	//por causa do split
	free(nome);
}
