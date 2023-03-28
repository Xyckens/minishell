/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:09:59 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/23 17:10:01 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freesplit(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
			if (s[i] == c[j] && i > 0 && s[i - 1] != c[0]
				&& s[i - 1] != c[1] && s[i - 1] != c[2])
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

char	**ft_alt_split(char *s, char *p)
{
	size_t	i;
	size_t	j;
	int		x;
	char	**ptrs;	

	ptrs = malloc((count_words(s, p) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	x = -1;
	while (i <= ft_strlen(s))
	{
		if (((s[i] != p[0] && s[i] != p[1] && s[i] != p[2])
				|| ((s[i] == p[0] || s[i] == p[1] || s[i] == p[2])
					&& between(s, i) == 0)) && x < 0)
			x = i;
		else if ((((s[i] == p[0] || s[i] == p[1] || s[i] == p[2])
					&& between(s, i) == 1) || i == ft_strlen(s)) && x >= 0)
		{
			ptrs[j++] = word_dup(s, x, i);
			x = -1;
		}
		i++;
	}
	ptrs[j] = 0;
	return (ptrs);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	count;
	char	*joined;

	count = -1;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	while (s1[++count] != '\0')
		joined[count] = s1[count];
	count = -1;
	while (s2[++count] != '\0')
		joined[len_s1 + count] = s2[count];
	joined[len_s1 + count] = '\0';
	free(s1);
	free(s2);
	return (joined);
}
