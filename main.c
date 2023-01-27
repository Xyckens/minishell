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

/*void ls(char *argv) 
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (argv)) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	  	if(ent->d_name[0] != '.')
	   	 printf ("%s   ", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  perror ("");
	}
	
}*/
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
	{
		echo(path);
	}
}

void	ft_export(char *command, char **envp)
{
	// static int	len;
	int			i;

	i = 0;
	if (!ft_strncmp(command, "export.", 7))
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		printf("%d\n", i);
	}
	else if (!ft_strncmp(command, "export ", 7))
	{	
		while (envp[i])
			i++;
		//len = i + 1;
		i++;
		if (ft_strchr(command, '='))
			envp[i] = &command[7];
		else
		{
			envp[i] = ft_strjoin(&command[7], "=''");			
			printf("Included: %s\n", envp[i]);
		}
		printf("%d\n", i);
	}
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
	char 			*line;

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
		ft_export(line, envp);
		path(line);
		free (line);
	}
	return (0);
}
