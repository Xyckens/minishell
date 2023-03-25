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

int	between2(const char *str, int pos)
{
	int	temp;
	int	flag;
	int	c;

	temp = -1;
	flag = 1;
	c = -1;
	while (str[++c] && c <= pos)
	{
		if (temp >= 0 && str[c] == str[temp])
		{
			temp = -1;
			flag = 1;
			continue ;
		}
		if (str[c] == 39 && temp == -1)
		{
			temp = c;
			flag = 0;
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	count_words2(char const *s, char *c)
{
	int	words;
	int	i;
	int	j;

	words = 1;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (j < 3)
		{	
			if (s[i] == c[j] && i > 0 && s[i - 1] != c[0]
				&& s[i - 1] != c[1] && s[i - 1] != c[2])
			{
				if (between2(s, i) == 1)
				{
					words++;
					break ;
				}
			}
			j++;
		}
		i++;
	}	
	return (words);
}

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
char	*join3strings(t_prompt *every, char *str, int c)
{
	int		temp;
	char	*tempstr;
	char	*tempstr2;

	temp = c;
	while (str[c] && str[c] != ' ' && str[c] != '"' && str[c] != 39
		&& str[c] != '>' && str[c] != '<' && str[c] != '|' && str[c] != '$')
		c++;
	tempstr2 = ft_substr(str, temp, c - temp);
	if (tempstr2[0] == '?')
	{
		free(tempstr2);
		tempstr2 = ft_itoa(every->exit_stat);
		tempstr = ft_alt_strjoin(ft_substr(str, 0, temp - 1), tempstr2);
	}
	else
		tempstr = ft_alt_strjoin(ft_substr(str, 0, temp - 1), get_variable(every, tempstr2));
	free(tempstr2);
	tempstr2 = ft_substr(str, c, ft_strlen(str + c));
	tempstr = ft_alt_strjoin(tempstr, tempstr2);
	free(tempstr2);
	return (tempstr);
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
			dlr[i] = join3strings(every, str[i], cou);
		else
			dlr[i] = ft_strdup(str[i]);
		i++;
	}
	freesplit(str);
	dlr[i] = 0;
	return (dlr);
}