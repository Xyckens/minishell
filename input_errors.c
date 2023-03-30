/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:42:26 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/27 20:54:06 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int moreerrors(char *str)
{
	int	c;

	c = 0;
	while (str[c])
	{
		if (c > 2 && (str[c] == '|' || str[c] == '<' || str[c] == '>'))
		{
			if (str[c] == str[c - 1]
				&& str[c] == str[c - 2])
				{
					ft_printf(2, "syntax error near %c\n", str[c]);
					return (1);
				}
		}
		c++;
	}
	return (0);
}

int	catch_input_errors(t_prompt *every)
{
	int	s;
	int	cexe;

	s = -1;
	cexe = 0;
	if (moreerrors(every->prompt) == 1)
		return (1);
	while (every->cmd[cexe])
		cexe++;
	while (every->sep[++s])
	{
		if (!every->cmd[s] || ft_strlen(every->cmd[s]) == 0)
			return (ft_printf(2, "syntax error near %c\n", every->sep[s][0]));
		if (every->sep[s][0] != every->sep[s][1] && every->sep[s][1] != '\0')
			return (ft_printf(2, "syntax error near %c\n", every->sep[s][0]));
	}
	if (cexe != s + 1 || cexe == 0)
	{
		ft_printf(2, "syntax error near %s\n", every->sep[s]);
		return (1);
	}
	return (0);
}
