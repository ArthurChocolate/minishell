/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:25:28 by tdelicia          #+#    #+#             */
/*   Updated: 2021/12/04 13:25:05 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size)
	{
		if (src[i] == '\0')
			break ;
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}
