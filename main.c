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

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf(1, "\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
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
	char		*line;
	int			fd;
	char		**new_env;
	t_prompt	nameit;

	(void)argv;
	(void)argc;
	new_env = set_new_env(envp);
	signals();
	line = "ola";
	while (line)
	{
		line = readline("prompt% ");
		if (!ft_strncmp (line, "exit", 4))
			break ;
		set_cmd(line, &nameit);
		add_history (line);
		fd = parser(line, new_env, &nameit);
	}
	free (line);
	if (fd != 1)
		close(fd);
	exit(1);
	return (0);
}
