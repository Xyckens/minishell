/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:21:42 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/13 15:01:22 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_prompt
{
	char	*cmd;
	char	*st_arg;
	int		fd;
	char	**new_env;
	int		exit_stat;
}				t_prompt;

void	path(char *path, t_prompt *first);
// Set arguments to list
void	set_cmd(char *path, t_prompt *first);
void	set_first_argument(char *path, t_prompt *first);

void	change_directory(t_prompt *every, char *pwd);
void	echo(char *str, t_prompt *every);

void	executable(char *prompt, t_prompt *everything);

char	**set_new_env(char **envp);
char	**ft_export(t_prompt *args);
char	**ft_unset(char *command, t_prompt *everything);

int		parser(char *prompt, t_prompt *first);
int		redirectout(char *prompt, int midle);
int		append(char *prompt, int midle);
char	*redirectin(char *prompt, int middle);

char	*name(char *str);
#endif
