/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegger-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:23:25 by jegger-s          #+#    #+#             */
/*   Updated: 2023/01/28 13:23:28 by jegger-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_export(char *command, char **new_env)
{
	int	i;
	
	i = 0;
	if (!ft_strncmp(command, "export.", 7))
	{
		while (new_env[i])
		{
			printf("%s\n", new_env[i]);
			i++;
		}
		printf("%d\n", i);
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
		printf("Included: %s\n", new_env[i]);
	}
	return (new_env);
}
