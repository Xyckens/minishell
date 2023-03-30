/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegger-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:27:03 by jegger-s          #+#    #+#             */
/*   Updated: 2023/03/30 22:27:05 by jegger-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '"')
		i--;
	key = ft_substr(str, 0, i);
	return (key);
}

char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	if (!strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	j = i;
	while (str[j])
		j++;
	value = ft_substr(str, i, j);
	return (value);
}

char	*get_default_key(t_prompt *every, int *i, char *var)
{
	char	*def_key;
	char	*new_key;

	new_key = get_key(var);
	while (every->new_env[*i])
	{
		def_key = get_key(every->new_env[*i]);
		if (!ft_strcmp(def_key, new_key))
			break ;
		free(def_key);
		def_key = NULL;
		(*i)++;
	}
	free(new_key);
	return (def_key);
}
