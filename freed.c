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
		//printf("arrraaaayyyy   %s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}
