/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:22:56 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/03 19:39:30 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	g_everything;

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf(1, "\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		g_everything.exit_stat = 130;
	}
}

void	signals(void)
{
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
		ft_printf(1, "failed to register interrupts with kernel\n");
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		ft_printf(1, "failed to register interrupts with kernel\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	g_everything.new_env = set_new_env(envp);
	signals();
	g_everything.exit_stat = 0;
	while (1)
	{
		g_everything.prompt = readline("prompt% ");
		if (!ft_strncmp (g_everything.prompt, "exit", 4))
			break ;
		sanitize(&g_everything);
		int i = 0;
		while (g_everything.cmd[i])
		{
			printf("%s\n", g_everything.cmd[i]);
			printf(" %s\n", g_everything.st_arg[i]);
			i++;
		}
		//g_everything.cmd = malloc(2 * sizeof(char*));
		//g_everything.st_arg = malloc(2 * sizeof(char*));
		set_cmd(&g_everything);
		add_history (g_everything.prompt);
		g_everything.fd = parser(&g_everything);
	}
	free (g_everything.prompt);
	if (g_everything.fd != 1)
		close(g_everything.fd);
	exit(1);
	return (0);
}
