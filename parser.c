/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:59:34 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/02 21:54:16 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_removeenv(char **new_env, int pos)
{
	int		count;

	count = pos;
	while (new_env[count + 1])
	{
		new_env[count] = new_env[count + 1];
		count++;
	}
	new_env[count] = NULL;
	return (new_env);
}

char	**ft_unset(char *command, char **new_env)
{
	int	count;
	int	i;

	count = 6;
	i = 0;
	if (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
	{
		ft_printf(2, "unset: not enough arguments\n");
	}
	else if (!ft_strncmp(command, "unset", 5))
	{
		while (command[count] && command[count] != ' ')
			count++;
		while (new_env[i])
		{
			if (!ft_strncmp(command + 6, new_env[i], count - 6))
			{
				new_env = ft_removeenv(new_env, i);
				break ;
			}
			i++;
		}
	}
	return (new_env);
}

void	path(char *path, int fd, char **new_env, t_prompt *first)
{
	char	pwd[1000];

	if (!ft_strcmp(first->cmd, "pwd"))
	{
		if (!ft_strcmp(first->st_arg, ""))
			ft_printf(fd, "%s\n", getcwd(pwd, 100));
		else
			ft_printf(fd, "pwd: too many arguments\n");
	}
	else if (!ft_strcmp(first->cmd, "cd"))
		change_directory(first->st_arg, fd, pwd);
	else if (!ft_strcmp(first->cmd, "echo"))
		echo(path, fd, new_env);
	else if (!ft_strcmp(first->cmd, "export")
		|| (!ft_strcmp(first->cmd, "unset")))
		printf(""); //Need to fix it.
	else
		executable(path, new_env, fd);
}

char	*formated_word(char *str)
{
	char	*new_word;
	int		i;
	int		j;

	new_word = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!new_word)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		new_word[j++] = str[i++];
	new_word[j++] = str[i++];
	new_word[j++] = '"';
	while (str[i])
		new_word[j++] = str[i++];
	new_word[j++] = '"';
	new_word[j] = '\0';
	return (new_word);
}

char	**ft_export(char **new_env, int fd, t_prompt *args)
{
	int	i;

	i = 0;
	if (!ft_strcmp(args->cmd, "export"))
	{
		if (!ft_strcmp(args->st_arg, ""))
		{
			while (new_env[i])
			{
				ft_printf(fd, "declare -x %s\n", new_env[i]);
				i++;
			}
		}
		else
		{
			while (new_env[i])
				i++;
			if (ft_strchr(args->st_arg, '='))
				new_env[i] = formated_word(args->st_arg);
			else
				new_env[i] = ft_strdup(args->st_arg);
		}
	}
	return (new_env);
}

int	parser(char *prompt, char **new_env, t_prompt *nameit)
{
	int	count;
	int	fd;

	count = 0;
	fd = 1;
	while (prompt[count])
	{
		/*if (prompt[count] == '|')
			pipe(prompt, count);*/
		/*if (prompt[count] == '<' && prompt[count + 1] == '<')
				delimiter(prompt, count++);
		else if (prompt[count] == '<' && prompt[count + 1] != '<')
				redirectin(prompt, count);
		}*/
		if (prompt[count] == '>' && prompt[count + 1] == '>')
			fd = append(prompt, count++);
		else if (prompt[count] == '>' && prompt[count + 1] != '>')
			fd = redirectout(prompt, count);
		count++;
	}
	new_env = ft_export(new_env, fd, nameit);
	new_env = ft_unset(prompt, new_env);
	path(prompt, fd, new_env, nameit);
	return (fd);
}
