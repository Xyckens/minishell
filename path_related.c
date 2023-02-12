/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:30:00 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/11 18:30:01 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(char *path, int fd, char *pwd)
{
	static char	*previuos_pwd;
	static char	*current_pwd;

	if (current_pwd != getcwd(pwd, 100))
		current_pwd = getcwd(pwd, 100);
	if (!ft_strcmp(path, "~") || !ft_strcmp(path, ""))
		chdir("/nfs/homes/jegger-s/");
	else if (!ft_strcmp(path, "-"))
	{
		chdir(previuos_pwd);
		ft_printf(fd, "%s\n", previuos_pwd);
	}
	else if (chdir(path) == -1)
		ft_printf(fd, "cd: %s: %s\n", strerror(errno), path);
	previuos_pwd = ft_strdup(current_pwd);
}

void	set_first_argument(char *path, t_prompt *first)
{
	int	st_arg;
	int	i;

	i = 0;
	while (path[i] && path[i] <= 32)
		i++;
	st_arg = i;
	while (path[st_arg] && path[st_arg] > 32)
		st_arg++;
	first->st_arg = malloc(sizeof(char) * st_arg + 1);
	st_arg = i;
	i = 0;
	while (path[st_arg] && path[st_arg] > 32)
		first->st_arg[i++] = path[st_arg++];
	first->st_arg[i] = '\0';
}

void	set_cmd(char *path, t_prompt *first)
{
	int	st_arg;
	int	cmd;
	int	i;

	i = 0;
	while (path[i] && path[i] <= 32)
		i++;
	cmd = i;
	while (path[cmd] && path[cmd] > 32)
		cmd++;
	st_arg = cmd;
	first->cmd = malloc(sizeof(char) * cmd + 1);
	cmd = i;
	i = 0;
	while (path[cmd] && path[cmd] > 32)
		first->cmd[i++] = path[cmd++];
	first->cmd[i] = '\0';
	set_first_argument(&path[st_arg], first);
}
