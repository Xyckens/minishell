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

int	count_words(char const *s, char *c)
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
			if (s[i] == c[j] && i > 0 && s[i - 1] != c[j])
			{
				if (between(s, i) == 1)
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

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_alt_split(char *s, char *sep)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**ptrs;	

	ptrs = malloc((count_words(s, sep) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (((s[i] != sep[0] && s[i] != sep[1] && s[i] != sep[2]) || ((s[i] == sep[0] || s[i] == sep[1] || s[i] == sep[2]) && between(s, i) == 0)) && index < 0)
			index = i;
		else if ((((s[i] == sep[0] || s[i] == sep[1] || s[i] == sep[2]) && between(s, i) == 1) || i == ft_strlen(s)) && index >= 0)
		{
			ptrs[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	ptrs[j] = 0;
	return (ptrs);
}

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

void	sanitize(t_prompt *every)
{
	char	**sep2;
	int		i;

	i = 0;
	sep2 = ft_alt_split(every->prompt, "><|");
	while (sep2[i])
		i++;
	every->cmd = malloc((i + 1) * sizeof(char *));
	every->st_arg = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (sep2[i])
	{
		//bro isto nao vai ficar nada assim, mas queria que ao menos
		//funcionasse
		char	**nome;

		nome = ft_split(ft_strtrim(sep2[i], " "), ' ');
		every->cmd[i] = nome[0];
		every->st_arg[i] = rest_of_promp(sep2[i]);
		i++;
	}
	every->sep = sep_init(every);
	every->cmd[i] = 0;
	every->st_arg[i] = 0;
	every->order = order(every);
}
