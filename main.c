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

char	**new_env = 0;

int	does_it_have_2quotes(char *str, int firststop)
{
	int count;
	int	count2;
	int	flag;

	count2 = 0;
	flag = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == 39)
			flag++;
		if (flag == 2)
		{
			count2 = count;
			break ;
		}
		count++;
	}
	if (flag == 2)
	{
		count = 0;
		while (str[count] && count < count2)
		{
			if (str[count] != 39)
				ft_putchar_fd(str[count], 1);
			count++;
		}
		return (firststop + count2 + 1);
	}
	return (firststop + 1);
}

void	ft_printenv(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == '=')
		{
			count++;
			break ;
		}
		count++;
	}
	while (str[count])
	{
		ft_putchar_fd(str[count], 1);
		count++;
	}
}

int dollarsign(char *str, int c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[count] && str[count] != ' ')
		count++;
	while (new_env[i])
	{
		if (!ft_strncmp(str, new_env[i], count))
		{
			ft_printenv(new_env[i]);
			break;
		}
		i++;
	}
	return (count + c + 1);
}

void	ft_epur(char *s)
{
	int c;
	int flag;
	int	l;

	c = 0;
	flag = 0;
	l = ft_strlen(s) - 1;
	while (s[c] != '\0' && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		c++;
	while (l > 0 && (s[l] == ' ' || s[l] == '\t' || s[l] == '\n'))
		l--;
	while (c <= l)
	{
		if (s[c] == 39)
			c = does_it_have_2quotes(s + c, c);
		if (s[c] == '$')
			c = dollarsign(s + c + 1, c);
		if (flag == 1 && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
		{
			ft_putchar_fd(' ', 1);
			flag = 0;
		}
		if (s[c] != ' ' && s[c] != '\t' && s[c] != '\n')
		{
			flag = 1;
			ft_putchar_fd(s[c], 1);
		}
		c++;
	}
}

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
	ft_epur(str + count);
	if (flag != 1)
		ft_putchar_fd('\n', 1);
}

void	path(char *path)
{
	char	pwd[1000];

	static char	*previuos_pwd;
	static char	*current_pwd;

	if (current_pwd != getcwd(pwd, 100))
		current_pwd = getcwd(pwd, 100);
	if (!ft_strncmp(path, "pwd", 3))
		printf("%s\n", getcwd(pwd, 100));
	else if (!ft_strncmp(path, "cd ", 3))
	{
		if (!ft_strncmp(&path[3], "~", 1))
			chdir("/nfs/homes/jegger-s/");
		else if (!ft_strncmp(&path[3], "-", 1))
		{
			chdir(previuos_pwd);
			printf("%s\n", previuos_pwd);
		}
		else if (chdir(&path[3]) == -1)
			printf("cd: %s: %s\n", strerror(errno), &path[3]);
		previuos_pwd = ft_strdup(current_pwd);
	}
	else if (!ft_strncmp(path, "echo ", 5))
		echo(path);
	/*else
		printf(" command not found: %s\n", path);*/ //vamos precisar disto, mas nao assim0
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

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	char 	*line;

	new_env = set_new_env(envp);
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
	{
		printf("failed to register interrupts with kernel\n");
	}
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
		new_env = ft_export(line, new_env);
		new_env = ft_unset(line, new_env);
		path(line);
		free (line);
	}
	return (0);
}
