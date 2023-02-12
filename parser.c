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

char	**ft_unset(char *command, t_prompt *every)
{
	int	count;
	int	i;

	count = 6;
	i = 0;
	if (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
	{
		ft_printf(2, "unset: not enough arguments\n");
		every->exit_stat = 1;
	}
	else if (!ft_strncmp(command, "unset", 5))
	{
		while (command[count] && command[count] != ' ')
			count++;
		while (every->new_env[i])
		{
			if (!ft_strncmp(command + 6, every->new_env[i], count - 6))
			{
				every->new_env = ft_removeenv(every->new_env, i);
				break ;
			}
			i++;
		}
			every->exit_stat = 0;
	}
	return (every->new_env);
}

void	path(char *path, t_prompt *every)
{
	char	pwd[1000];

	if (!ft_strcmp(every->cmd, "pwd"))
	{
		if (!ft_strcmp(every->st_arg, ""))
		{
			ft_printf(every->fd, "%s\n", getcwd(pwd, 100));
			every->exit_stat = 0;
		}
		else
		{
			ft_printf(every->fd, "pwd: too many arguments\n");
			every->exit_stat = 1;
		}
	}
	else if (!ft_strcmp(every->cmd, "cd"))
		change_directory(every, pwd);
	else if (!ft_strcmp(every->cmd, "echo"))
		echo(path, every);
	else if (!ft_strcmp(every->cmd, "export")
		|| (!ft_strcmp(every->cmd, "unset")))
		printf(""); //Need to fix it.
	else
		executable(path, every);
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

char	**ft_export(t_prompt *every)
{
	int	i;

	i = 0;
	if (!ft_strcmp(every->cmd, "export"))
	{
		if (!ft_strcmp(every->st_arg, ""))
		{
			//nao funciona para "export > test"
			//se calhar resolvemos isso no parcer, mas explico te em pessoa
			//printf("%d\n", every->fd);
			while (every->new_env[i])
			{
				ft_printf(every->fd, "declare -x %s\n", every->new_env[i]);
				i++;
			}
			every->exit_stat = 0;
		}
		else
		{
			while (every->new_env[i])
				i++;
			if (ft_strchr(every->st_arg, '='))
				every->new_env[i] = formated_word(every->st_arg);
			else
				every->new_env[i] = ft_strdup(every->st_arg);
			//nao tenho a certeza disto
			every->exit_stat = 0;
		}
	}
	//precisamos de if para quando export nao funciona
	// o export consegue nao funcionar? lol nao sei
	return (every->new_env);
}

int	parser(char *prompt, t_prompt *everything)
{
	int	count;

	count = 0;
	everything->fd = 1;
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
			everything->fd = append(prompt, count++);
		else if (prompt[count] == '>' && prompt[count + 1] != '>')
			everything->fd = redirectout(prompt, count);
		count++;
	}
	everything->new_env = ft_export(everything);
	everything->new_env = ft_unset(prompt, everything);
	path(prompt, everything);
	return (everything->fd);
}
