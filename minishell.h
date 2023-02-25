/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:21:42 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/17 20:13:48 by fvieira          ###   ########.fr       */
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
	char	*prompt;
	char	**cmd;
	char	**st_arg;
	char	**sep;
	int		*order;
	int		fd;
	char	**new_env;
	int		exit_stat;
}				t_prompt;

int		count_words(char const *s, char *c);
int		*order(t_prompt *every);
char	**sep_init(t_prompt *e);
void	sanitize(t_prompt *every);
int		between(const char *str, int pos);

void	path(t_prompt *every, int c);

void	change_directory(t_prompt *every, char *pwd);
void	echo(t_prompt *every, int c);

void	executable(t_prompt *everything, int c);

char	**set_new_env(char **envp);
char	**ft_export(t_prompt *args);
char	**ft_unset(t_prompt *everything, int c);

int		parser(t_prompt *every);
int		redirectout(char *prompt);
int		append(char *prompt);
char	*redirectin(char *prompt);

char	*name(char *str);

void	freesplit(char **array);
void	delete_everything(t_prompt *everything);
#endif
