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

/*char	*get_default_key(t_prompt *every, int *i, int c)
{
	char	*def_key;
	char	*new_key;

	new_key = get_key(every->st_arg[c]);
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
}*/
//	&& validate_variables(var[count], 0))
char	**create_new_var(t_prompt *every, int i, char *var)
{
	if (!ft_strchr(var, '='))
		every->new_env[i++] = ft_strdup(var);
	else
	{
		free(every->new_env[i]);
		every->new_env[i++] = formated_word(var);
	}
	return (every->new_env);
}

/*char	**create_new_var(t_prompt *every, int i, int c)
{
	char 	**var;
	int 	count;
	
	count = count_words(every->st_arg[c], " \t\n");
	var = ft_alt_split(every->st_arg[c], " \t\n");
	every->new_env = set_new_env2(every->new_env, every, i + count + 2);
	count = 0;
	while (var[count])
	{
		// def_key = get_default_key(every, &i, c);
		if (!ft_strchr(var[count], '=')) //	&& validate_variables(var[count], 0))
		{
			printf("WORD == %s\n", var[count]);
			printf("new_env[i] == %s\n", every->new_env[i]);
			every->new_env[i++] = ft_strdup(var[count++]);
		}
		else
		{
			printf("WORD: %s\n", var[count]);
			free(every->new_env[i]);
			every->new_env[i++] = formated_word(var[count++]);
		}
	}
	freesplit(var);
	return (every->new_env);
}*/

char	**manage_env_variables(t_prompt *every, int c, int i)
{
	char	*new_value;
	char	*def_key;
	char	**var;
	int		count;

	while (every->new_env[i])
		i++;
	count = count_words(every->st_arg[c], " \t\n");
	var = ft_alt_split(every->st_arg[c], " \t\n");
	every->new_env = set_new_env2(every->new_env, every, i + count + 2);
	count = -1;
	while (var[++count])
	{
		i = 0;
		def_key = get_default_key(every, &i, var[count]);
		new_value = get_value(every->st_arg[c]);
		if ((!def_key && !new_value) || new_value)
			every->new_env = create_new_var(every, i, var[count]);
		if (def_key)
			free(def_key);
		free(new_value);
	}
	freesplit(var);
	every->exit_stat = 0;
	return (every->new_env);
}

/*char	**manage_env_variables(t_prompt *every, int c, int i)
{
	char	*def_key;
	char	*new_value;

	def_key = get_default_key(every, &i, c);
	new_value = get_value(every->st_arg[c]);
	if ((!def_key && !new_value) && validate_variables(every->st_arg[c], 0))
	{
		every->new_env = set_new_env2(every->new_env, every, i + 1);
		every->new_env[i] = ft_strdup(every->st_arg[c]);
	}
	else if (new_value && validate_variables(get_key(every->st_arg[c]), 1))
	{
		if (!every->new_env[i])
			every->new_env = set_new_env2(every->new_env, every, i + 1);
		else
			free(every->new_env[i]);
		every->new_env[i] = formated_word(every->st_arg[c]);
	}
	if (def_key)
		free(def_key);
	free(new_value);
	every->exit_stat = 0;
	return (every->new_env);
}*/

char	**ft_export(t_prompt *e, int c)
{
	int	i;

	i = 0;
	if (e->st_arg[c][0] == '\0')
	{
		while (e->new_env[i])
		{
			c = -1;
			ft_printf(e->fd, "declare -x ");
			while (e->new_env[i][++c])
			{
				ft_putchar_fd(e->new_env[i][c], e->fd);
				if ((e->new_env[i][c] == '=' && e->new_env[i][c + 1] != '"')
				|| (ft_strchr(e->new_env[i], '=') && (e->new_env[i][c + 1] == 0
				&& e->new_env[i][c] != '"')))
					ft_putchar_fd('"', e->fd);
			}
			ft_putchar_fd('\n', e->fd);
			i++;
		}
		e->exit_stat = 0;
	}
	else
		e->new_env = manage_env_variables(e, c, 0);
	return (e->new_env);
}
