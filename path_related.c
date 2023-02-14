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

void	change_directory(t_prompt *every, char *pwd)
{
	static char	*previuos_pwd;
	static char	*current_pwd;

	every->exit_stat = 0;
	if (current_pwd != getcwd(pwd, 100))
		current_pwd = getcwd(pwd, 100);
	if (!ft_strcmp(every->st_arg[0], "~") || !ft_strcmp(every->st_arg[0], ""))
		chdir("/nfs/homes/jegger-s/");
	else if (!ft_strcmp(every->st_arg[0], "-"))
	{
		if (!previuos_pwd)
			ft_printf(every->fd, "%s\n", current_pwd);
		else
		{
			chdir(previuos_pwd);
			ft_printf(every->fd, "%s\n", previuos_pwd);
		}
	}
	else if (chdir(every->st_arg[0]) == -1)
		ft_printf(every->fd, "cd: %s: %s\n", strerror(errno), every->st_arg[0]);
	//nao estou a acompanhar isto, depois confirma se nao deverias
	//estar a escrever para fd = 2, se 'e error aposto q sim
	//depois preciso q ponhas o every->exit_stat conforme o cd do terminal
	previuos_pwd = ft_strdup(current_pwd);
	//where free?
}

void	set_first_argument(char *path, t_prompt *every)
{
	int	st_arg;
	int	i;

	i = 0;
	while (path[i] && path[i] <= 32)
		i++;
	st_arg = i;
	while (path[st_arg] && path[st_arg] > 32)
		st_arg++;
	every->st_arg[0] = malloc(sizeof(char) * st_arg + 1);
	st_arg = i;
	i = 0;
	while (path[st_arg] && path[st_arg] > 32)
		every->st_arg[0][i++] = path[st_arg++];
	every->st_arg[0][i] = '\0';
}

void	set_cmd(t_prompt *every)
{
	int	st_arg;
	int	cmd;
	int	i;

	i = 0;
	while (every->prompt[i] && every->prompt[i] <= 32)
		i++;
	cmd = i;
	while (every->prompt[cmd] && every->prompt[cmd] > 32)
		cmd++;
	st_arg = cmd;
	every->cmd[0] = malloc(sizeof(char) * cmd + 1);
	cmd = i;
	i = 0;
	while (every->prompt[cmd] && every->prompt[cmd] > 32)
		every->cmd[0][i++] = every->prompt[cmd++];
	every->cmd[0][i] = '\0';
	set_first_argument(&every->prompt[st_arg], every);
}
