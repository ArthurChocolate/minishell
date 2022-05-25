/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointerpointer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:19:31 by tdelicia          #+#    #+#             */
/*   Updated: 2021/12/09 15:20:42 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_pointerpointer(char **pathvar)
{
	char	**tmp;

	tmp = pathvar;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(pathvar);
}
