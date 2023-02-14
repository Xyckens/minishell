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

/*int	check_duplicate_keys(t_prompt *every)
{
	int	i;
	int	j;

	i = 0;
	while (every->new_env[i])
	{
		j = 0;
		while (every->st_arg[j])
		{
			if (every->st_arg[j] != every->new_env[i][j])
				break ;
			j++:
		}
		i++;
	}
	return ()
}*/

char	**ft_export(t_prompt *every)
{
	int	i;

	i = 0;
	if (!ft_strcmp(every->cmd[0], "export"))
	{
		if (!ft_strcmp(every->st_arg[0], ""))
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
			if (ft_strchr(every->st_arg[0], '='))
				every->new_env[i] = formated_word(every->st_arg[0]);
			else
				every->new_env[i] = ft_strdup(every->st_arg[0]);
			//nao tenho a certeza disto
			every->exit_stat = 0;
		}
	}
	//precisamos de if para quando export nao funciona
	// o export consegue nao funcionar? lol nao sei
	return (every->new_env);
}

void	path(t_prompt *every)
{
	char	pwd[1000];

	if (!ft_strcmp(every->cmd[0], "pwd"))
	{
		if (!ft_strcmp(every->st_arg[0], ""))
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
	else if (!ft_strcmp(every->cmd[0], "cd"))
		change_directory(every, pwd);
	else if (!ft_strcmp(every->cmd[0], "echo"))
		echo(every);
	else if (!ft_strcmp(every->cmd[0], "export"))
		every->new_env = ft_export(every);
	else if (!ft_strcmp(every->cmd[0], "unset"))
		every->new_env = ft_unset(every->prompt, every);
	else
		executable(every);
}

int	parser(t_prompt *eve)
{
	int	c;

	c = 0;
	eve->fd = 1;
	while (eve->prompt[c])
	{
		/*if (eve->prompt[c] == '|')
			pipe(eve->prompt, c);*/
		/*if (eve->prompt[c] == '<' && eve->prompt[c + 1] == '<')
				delimiter(eve->prompt, c++);*/
		if (eve->prompt[c] == '<' && eve->prompt[c + 1] != '<')
			eve->prompt = redirectin(eve->prompt, c);
		else if (eve->prompt[c] == '>' && eve->prompt[c + 1] == '>')
			eve->fd = append(eve->prompt, c++);
		else if (eve->prompt[c] == '>' && eve->prompt[c + 1] != '>')
			eve->fd = redirectout(eve->prompt, c);
		c++;
	}
	path(eve);
	return (eve->fd);
}