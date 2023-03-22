/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:39:44 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/17 19:29:04 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rest_of_promp(char *sep)
{
	int		count;
	int		final;
	char	*str;

	count = 0;
	final = 0;
	while (sep[count] == ' ')
		count++;
	while (sep[count] != ' ' && sep[count])
		count++;
	while (sep[count] == ' ')
		count++;
	while (sep[count + final])
		final++;
	str = malloc(final + 1);
	final = 0;
	while (sep[count + final])
	{
		str[final] = sep[count + final];
		final++;
	}
	str[final] = '\0';
	return (str);
}

void	ft_prompt(t_prompt *every, char *prompt, int i)
{
	char	**sep;
	char	*joined;
	int		j;

	sep = ft_alt_split(prompt, " \t");
	joined = ft_strdup("\0");
	j = 0;
	if (sep[0])
		every->cmd[i] = ft_strtrim(sep[0], "\"");
	else
		every->cmd[i] = ft_strdup("\0");
	while (sep[0] && sep[++j])
	{
		if (j > 1)
			joined = ft_alt_strjoin(joined, " ");
		joined = ft_alt_strjoin(joined, sep[j]);
	}
	if (!sep[1])
		every->st_arg[i] = ft_strdup("\0");
	else
		every->st_arg[i] = ft_strdup(joined);
	free(joined);
	freesplit(sep);
}

void	sanitize(t_prompt *every)
{
	char	**sep2;
	int		i;

	i = 0;
	sep2 = ft_alt_split(every->prompt, "><|");
	while (sep2[i])
		i++;
	delete_everything(every);
	if (i == 0)
		i++;
	every->cmd = malloc((i + 1) * sizeof(char *));
	every->st_arg = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (sep2[++i])
		ft_prompt(every, sep2[i], i);
	if (!sep2[0])
	{
		every->st_arg[i] = ft_strdup("\0");
		every->cmd[i++] = ft_strdup("\0");
	}
	every->cmd[i] = 0;
	every->st_arg[i] = 0;
	every->sep = sep_init(every);
	every->order = order(every);
	freesplit(sep2);
}
