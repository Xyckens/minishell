/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:23:25 by jegger-s          #+#    #+#             */
/*   Updated: 2023/02/01 17:11:56 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(char *command, char **new_env, int fd)
{
	int	i;
	
	i = 0;
	if (!ft_strncmp(command, "export.", 7))
	{
		while (new_env[i])
		{
			ft_printf(fd, "%s\n", new_env[i]);
			i++;
		}
		ft_printf(fd, "%d\n", i);
	}
	else if (!ft_strncmp(command, "export ", 7))
	{
		while (new_env[i])
			i++;
		if (ft_strchr(command, '='))
			new_env[i] = ft_strdup(&command[7]);
		else
		{
			new_env[i] = ft_strjoin(&command[7], "=''");
		}
		ft_printf(fd, "Included: %s\n", new_env[i]);
	}
	return (new_env);
}
