/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:22:56 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/27 22:13:08 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	g_everything;

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_everything.exit_stat = 130;
	}
}

void	signals(void)
{
	struct termios termios_save;
	struct termios termios_new;

	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		ft_printf(1, "failed to register interrupts with kernel\n");
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		ft_printf(1, "failed to register interrupts with kernel\n");
	if (tcgetattr(0, &termios_save) == -1) 
	{
		perror("tcgetattr"); 
		exit(1); 
	}
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new) == -1) 
	{
		perror("tcsetattr"); 
		exit(1); 
	}
}

void	delete_everything(t_prompt *everything)
{
	if (everything->cmd)
		freesplit(everything->cmd);
	if (everything->sep)
		freesplit(everything->sep);
	if (everything->st_arg)
		freesplit(everything->st_arg);
	free(everything->order);
}

void	ft_exit(t_prompt *everything)
{
	int	saida;
	if (!everything->st_arg[0])
		saida = (everything->exit_stat);
	else
		saida = (ft_atoi(everything->st_arg[0]));
	change_directory(everything, "altura de dar free a isto!@#%$^");
	delete_everything(everything);
	freesplit(everything->new_env);
	ft_printf(1, "exit\n");
	exit(saida);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	signals();
	g_everything.new_env = set_new_env(envp);
	g_everything.exit_stat = 0;
	g_everything.herein = 0;
	g_everything.clean = 0;
	g_everything.parser = 0;
	while (1)
	{
		if (!g_everything.herein)
		{
			g_everything.parser = 0;
			g_everything.clean = 0;
			g_everything.prompt = readline("prompt% ");
		}
		if (!g_everything.prompt)
			exit(g_everything.exit_stat);
		if (!g_everything.clean)
			sanitize(&g_everything);
		if (!ft_strcmp(g_everything.cmd[0], "exit"))
			ft_exit(&g_everything);
		if (g_everything.prompt[0] != '\0')
			add_history(g_everything.prompt);
		if (!catch_input_errors(&g_everything)
			&& g_everything.prompt[0] != 0 && ft_strlen(g_everything.cmd[0]))
			g_everything.fd = parser(&g_everything);
		free(g_everything.prompt);
	}
	return (0);
}
		/*int i = 0;
		while (g_everything.cmd[i])
		{
			printf("executable = %s\n", g_everything.cmd[i]);
			printf("  args     = %s\n", g_everything.st_arg[i]);
			printf("   sep     = %s\n", g_everything.sep[i]);
			printf("  order    = %d\n", g_everything.order[i]);
			i++;
		}*/
