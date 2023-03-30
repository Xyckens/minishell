/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegger-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:06:05 by jegger-s          #+#    #+#             */
/*   Updated: 2023/01/28 14:06:07 by jegger-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	get_sizeof_envp(char **envp)
{
	size_t	total_length;
	int		i;

	i = -1;
	total_length = 0;
	while (envp[++i])
		total_length += ft_strlen(envp[i]);
	return (total_length + i);
}

char	**set_new_env(char **envp)
{
	size_t	total_length;
	char	**new_env;
	int		i;

	total_length = get_sizeof_envp(envp);
	new_env = malloc(sizeof(char *) * (total_length + 1));
	i = -1;
	while (envp[++i])
		new_env[i] = ft_strdup(envp[i]);
	new_env[i] = 0;
	return (new_env);
}

char	**set_new_env2(char **envp, t_prompt *every, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		new_env[i] = ft_strdup(envp[i]);
	new_env[i] = 0;
	new_env[i + 1] = 0;
	freesplit(every->new_env);
	return (new_env);
}
