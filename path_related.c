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

char	*ft_str_nex_chr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == c)
			return ((char *)s + count + 1);
		count++;
	}
	if (s[count] == c)
		return ((char *)s + count + 1);
	return (0);
}

char	*get_variable(t_prompt *env, char *var)
{
	int		i;

	i = 0;
	while (env->new_env[i])
	{
		if (!ft_strncmp(env->new_env[i], var, ft_strlen(var)))
			return (ft_str_nex_chr(env->new_env[i], '='));
		i++;
	}
	return (NULL);
}

void	change_directory(t_prompt *every, char *pwd)
{
	static char	*previous_pwd;
	static char	*current_pwd;
	char		*var;

	every->exit_stat = 0;
	if (!ft_strcmp(pwd, "altura de dar free a isto!@#%$^"))
	{
		if (previous_pwd)
			free(previous_pwd);
		return ;
	}
	if (current_pwd != getcwd(pwd, 100))
		current_pwd = getcwd(pwd, 100);
	if (!ft_strcmp(every->st_arg[0], "~") || !ft_strcmp(every->st_arg[0], ""))
		chdir(get_variable(every, "HOME"));
	else if (!ft_strncmp(every->st_arg[0], "$", 1))
	{
		var = ft_str_nex_chr(every->st_arg[0], '$');
		if (!get_variable(every, var))
			chdir(get_variable(every, "HOME"));
		else if (chdir(get_variable(every, var)) == -1)
			ft_printf(2, "cd: %s: %s\n", get_variable(every, var), strerror(errno));
	}
	else if (!ft_strcmp(every->st_arg[0], "-"))
	{
		if (!previous_pwd)
			ft_printf(every->fd, "%s\n", current_pwd);
		else
		{
			chdir(previous_pwd);
			ft_printf(every->fd, "%s\n", previous_pwd);
		}
	}
	else if (chdir(every->st_arg[0]) == -1)
		ft_printf(2, "cd: %s: %s\n", every->st_arg[0], strerror(errno));
	if (previous_pwd)
		free(previous_pwd);
	previous_pwd = ft_strdup(current_pwd);
}
