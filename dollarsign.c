/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:59:02 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/25 11:59:03 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_alt_strchr(const char *s, char d)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		if (s[count] == d)
			return (count);
		count++;
	}
	return (-1);
}

char	*joinrest(t_prompt *every, char *str, char *tempstr2, int temp)
{
	char	*var;
	char	*tempstr;

	var = ft_strdup(tempstr2 + temp - 1);
	tempstr = ft_substr(str, 0, temp - 1);
	free(tempstr2);
	tempstr2 = ft_strjoinfree(tempstr, join3strings(every, var, 1, 1));
	free(var);
	return (tempstr2);
}

char	*join3strings(t_prompt *every, char *str, int c, int temp)
{
	char	*tempstr;
	char	*tempstr2;
	char	*var;

	while (str[c] && str[c] != ' ' && str[c] != '"' && str[c] != 39
		&& (str[c] > 62 || str[c] < 60) && str[c] != '|' && str[c] != '$')
		c++;
	tempstr2 = ft_substr(str, temp, c - temp);
	if (tempstr2[0] == '?')
	{
		free(tempstr2);
		tempstr2 = ft_itoa(every->exit_stat);
		tempstr = ft_alt_strjoin(ft_substr(str, 0, temp - 1), tempstr2);
	}
	else
	{
		var = get_variable(every, tempstr2);
		tempstr = ft_alt_strjoin(ft_substr(str, 0, temp - 1), var);
	}
	free(tempstr2);
	tempstr2 = ft_substr(str, c, ft_strlen(str + c));
	temp = ft_alt_strchr(str + c - 1, '$');
	if (temp > -1)
		tempstr2 = joinrest(every, str + c, tempstr2, temp);
	return (ft_strjoinfree(tempstr, tempstr2));
}

char	**dollarsign2(t_prompt *every, char **str)
{
	int		i;
	int		cou;
	char	**dlr;

	i = 0;
	while (str[i])
		i++;
	dlr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		cou = ft_alt_strchr(str[i], '$');
		if (ft_strnstr(str[i], "export", 7))
			cou = -2;
		if (cou++ >= 0 && between2(str[i], ft_alt_strchr(str[i], '$')))
			dlr[i] = join3strings(every, str[i], cou, cou);
		else
			dlr[i] = ft_strdup(str[i]);
		i++;
	}
	freesplit(str);
	dlr[i] = 0;
	return (dlr);
}
