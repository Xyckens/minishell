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

/*char	**ft_export(t_prompt *every)
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
}*/

void	path(t_prompt *every, int c)
{
	char	pwd[1000];

	if (!ft_strcmp(every->cmd[c], "pwd"))
	{
		ft_printf(every->fd, "%s\n", getcwd(pwd, 100));
		every->exit_stat = 0;
	}
	else if (!ft_strcmp(every->cmd[c], "cd"))
		change_directory(every, pwd);
	else if (!ft_strcmp(every->cmd[c], "echo"))
		echo(every, c);
	else if (!ft_strcmp(every->cmd[c], "export"))
		every->new_env = ft_export(every);
	else if (!ft_strcmp(every->cmd[c], "unset"))
		every->new_env = ft_unset(every->prompt, every);
	else if (!ft_strcmp(every->cmd[c], "exit"))
	{
		ft_printf(1, "exit: too many arguments\n");
		every->exit_stat = 1;
	}
	else
		executable(every, c);
}

int	parser(t_prompt *eve)
{
	//static int	c = 0;
	int	c;

	c = 0;
	eve->fd = 1;
	while (eve->cmd[c])
	{
		//if (eve->sep[c] == '|')
		//	pipes(eve, c);
		// if (eve->sep[c] == '<' && eve->sep[c + 1] == '<')
		// 		delimiter(eve->sep, c++);
		// if (eve->sep[c][0] == '<' && eve->sep[c][1] != '<')
		// 	eve->prompt = redirectin(eve->cmd[1]);
		if (eve->sep[c] && eve->sep[c][0] == '>' && eve->sep[c][1] == '>')
			eve->fd = append(eve->cmd[c + 1]);
		else if (eve->sep[c] && eve->sep[c][0] == '>' && eve->sep[c][1] != '>')
			eve->fd = redirectout(eve->cmd[c + 1]);
		path(eve, c);
		c++;
	}
	return (eve->fd);
}
