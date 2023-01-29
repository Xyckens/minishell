/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:32:43 by fvieira           #+#    #+#             */
/*   Updated: 2023/01/29 14:32:47 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_removeenv(char **new_env, int pos)
{
	int		count;

	count = pos;
	while (new_env[count + 1])
	{
		new_env[count] = new_env[count + 1];
		count++;
	}
	new_env[count] = NULL;
	return (new_env);
}

char	**ft_unset(char *command, char **new_env)
{
	int	count;
	int	i;
	
	count = 6;
	i = 0;
	if (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
	{
		printf("unset: not enough arguments\n");
	}
	else if (!ft_strncmp(command, "unset", 5))
	{
		while (command[count] && command[count] != ' ')
			count++;
		while (new_env[i])
		{
			if (!ft_strncmp(command + 6, new_env[i], count - 6))
			{
				new_env = ft_removeenv(new_env, i);
				break;
			}
			i++;
		}
	}
	return (new_env);
}