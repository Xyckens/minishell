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

int	catch_input_errors(t_prompt *every)
{
	int	s;
	int	cexe;

	s = -1;
	cexe = 0;
	while (every->cmd[cexe])
		cexe++;
	while (every->sep[++s])
	{
		if (!every->cmd[s] || ft_strlen(every->cmd[s]) == 0)
		{
			ft_printf(2, "syntax error near unexpected token %c\n", every->sep[s][0]);
			return (0);
		}
		if (every->sep[s][0] != every->sep[s][1] && every->sep[s][1] != '\0')
		{
			ft_printf(2, "syntax error near unexpected token %c\n", every->sep[s][0]);
			return (0);
		}
	}
	if (cexe != s + 1 || cexe == 0)
	{
		ft_printf(2, "syntax error near unexpected token %s\n", every->sep[s]);
		return (0);
	}
	return (1);
}
