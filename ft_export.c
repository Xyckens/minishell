/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:20:49 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/17 13:20:50 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_setchar(char *str, char get, char set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == get)
			str[i] = set;
		i++;
	}
	return (str);
}

char	*formated_word(char *str)
{
	char	*new_word;
	int		i;
	int		j;

	str = ft_setchar(str, 39, '"');
	if (strchr(str, '"'))
		return (str);
	new_word = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!new_word)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		new_word[j++] = str[i++];
	new_word[j++] = str[i++];
	new_word[j++] = '"';
	while (str[i])
		new_word[j++] = str[i++];
	new_word[j++] = '"';
	new_word[j] = '\0';
	return (new_word);
}

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
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

char	**manage_env_variables(t_prompt *every, int c)
{
	char	*def_key;
	char	*new_key;
	char	*new_value;
	int		i;

	i = -1;
	new_key = get_key(every->st_arg[c]);
	while (every->new_env[++i])
	{
		def_key = get_key(every->new_env[i]);
		if (!ft_strcmp(def_key, new_key))
			break ;
		free(def_key);
		def_key = NULL;
	}
	new_value = get_value(every->st_arg[c]);
	if (new_value)
	{
		every->new_env = set_new_env2(every->new_env, every, i + 1);
		every->new_env[i] = formated_word(every->st_arg[c]);
	}
	else if (!def_key && !new_value)
	{
		every->new_env = set_new_env2(every->new_env, every, i + 1);
		every->new_env[i] = ft_strdup(every->st_arg[c]);
	}
	free(new_value);
	free(new_key);
	every->exit_stat = 0;
	return (every->new_env);
}

char	**ft_export(t_prompt *e, int c)
{
	int		i;

	i = 0;
	if (e->st_arg[c][0] == '\0')
	{
		while (e->new_env[i])
		{
			c = -1;
			ft_printf(e->fd, "declare -x ");
			while (e->new_env[i][++c])
			{
				ft_putchar_fd(e->new_env[i][c],e->fd);
				if ((e->new_env[i][c] == '=' && e->new_env[i][c + 1] != '"')
					|| (e->new_env[i][c + 1] == 0 && e->new_env[i][c] != '"'))
					ft_putchar_fd('"', e->fd);
			}
			ft_putchar_fd('\n', e->fd);
			i++;
		}
		e->exit_stat = 0;
	}
	else
		e->new_env = manage_env_variables(e, c);
	return (e->new_env);
}
