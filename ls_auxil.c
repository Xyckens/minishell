/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsauxil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:57:52 by fvieira           #+#    #+#             */
/*   Updated: 2023/01/26 21:57:53 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* joao, deves ler isto antes de falarmos, so para saberes o que estava a tentar fazer:
o ls por enquanto esta a dar as coisas sem estarem ordenadas alfabeticamente, na funcao scandir
podes la por um alphasort qualquer mas tecnicamente iso 'e uma funcao nao autorizada, embora ache que ninguem
notasse 'e melhor nao! por isso estava aqui a tentar fazer  das minhas, mas ja 'e tarde e nao estou a conseguir
outra possivel solucao podera ser ordenar QUANDO se printa em vez da estrutura em si,
amanha fala se
*/
void	alphabeticsort(struct dirent **str)
{
	int	count;
	int max_len;
	char	*temp;

	count = 0;

	printf("%s",str[0]->d_name);
	while (str[count + 1]->d_name->d_name)
	{
		if (ft_strlen(str[count]->d_name) < ft_strlen(str[count + 1]->d_name))
			max_len = ft_strlen(str[count]->d_name);
		else
			max_len = ft_strlen(str[count + 1]->d_name);
		if (ft_strncmp(str[count]->d_name, str[count + 1]->d_name, max_len) > 0)
		{
			temp = str[count + 1]->d_name;
			str[count + 1]->d_name = str[count]->d_name;
			str[count]->d_name = temp;
			count = 0;
		}
	}
}