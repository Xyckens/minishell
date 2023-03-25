/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:21:42 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/27 15:48:27 by fvieira          ###   ########.fr       */
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
# include <termios.h>

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
	int		herein;
	int		clean;
	int		parser;
}				t_prompt;

int		count_words(char const *s, char *c);
int		*order(t_prompt *every);
char	**sep_init(t_prompt *e);
void	sanitize(t_prompt *every);
int		between(const char *str, int pos);

int		catch_input_errors(t_prompt *every);

void	path(t_prompt *every, int c);

void	change_directory(t_prompt *every, char *pwd);
char	*get_variable(t_prompt *env, char *var);

void	echo(t_prompt *every, int c);

char	**initialize(t_prompt *everything, int c);
void	idk(char *arg0, char **args, t_prompt *everything, int c);
int		executable(t_prompt *everything, int c);

char	**set_new_env(char **envp);
char	**set_new_env2(char **envp, t_prompt *every, int size);
char	**ft_export(t_prompt *every, int c);
char	**ft_unset(t_prompt *everything, int c);

int		parser(t_prompt *every);
int		redirectout(char *prompt);
int		append(char *prompt);
int		redirectin(char *name);
int		hereindoc(t_prompt *every);
void	mult_pipes(t_prompt *every, int c, int mult);

char	*name(char *str);

void	freesplit(char **array);
char	**ft_alt_split(char *s, char *p);
void	delete_everything(t_prompt *everything);
char	**dollarsign2(t_prompt *every, char **str);
#endif
