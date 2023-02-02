/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:59:34 by fvieira           #+#    #+#             */
/*   Updated: 2023/02/02 21:54:16 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *prompt)
{
	int	count;
	int	fd;

	count = 0;
	fd = 1;
	/*while (prompt[count])
	{
		if (prompt[count] == '|')
			pipe(prompt, count);
		else if (prompt[count] == '<')
		{
			if (prompt[count + 1] == '<')
				delimiter(prompt, count++);
			else
				redirectin(prompt, count);
		}
		else if (prompt[count] == '>')
		{
			if (prompt[count + 1] == '>')
				fd = append(prompt, count++);
			else
				fd = redirectout(prompt, count);
		}
		count++;
	}*/
	return (fd);
}