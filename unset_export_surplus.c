/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export_surplus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:55:53 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/28 17:55:54 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	several_unset(char *st_arg, t_prompt *every)
{
	char	**rem;
	int		cou;
	int		i;

	cou = 0;
	rem = ft_split(st_arg, ' ');
	while (rem[cou])
		cou++;
	while (--cou >= 0)
	{
		i = -1;
		while (every->new_env[++i])
		{
			if (!ft_strncmp(rem[cou], every->new_env[i], ft_strlen(rem[cou])))
			{
				every->new_env = ft_removeenv(every->new_env, i);
				break ;
			}
		}
	}
	freesplit(rem);
}

char	**ft_unset(t_prompt *every, int c)
{
	if (!every->st_arg[c])
	{
		ft_printf(2, "unset: not enough arguments\n");
		every->exit_stat = 1;
	}
	else
	{
		several_unset(every->st_arg[c], every);
		every->exit_stat = 0;
	}
	return (every->new_env);
}

char	*formated_word(char *str)
{
	char	*new_word;
	int		i;
	int		j;

	str = ft_setchar(str, 39, '"');
	if (strchr(str, '"'))
		return (str);
	new_word = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_word)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		new_word[j++] = str[i++];
	new_word[j++] = str[i++];
	while (str[i])
		new_word[j++] = str[i++];
	new_word[j] = '\0';
	return (new_word);
}
