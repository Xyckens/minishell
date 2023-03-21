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
	int	csep;
	int	cexe;

	csep = 0;
	cexe = 0;
	while (every->cmd[cexe])
		cexe++;
	while (every->sep[csep])
	{
		if (!every->cmd[csep])
		{
			ft_printf(2, "error near %s\n", every->sep[csep]);
			return (0);
		}
		csep++;
	}
	if (cexe != csep + 1 || cexe == 0)
	{
		ft_printf(2, "error near %s\n", every->sep[csep]);
		return (0);
	}
	return (1);
}
