/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:19:38 by tdelicia          #+#    #+#             */
/*   Updated: 2021/10/08 18:30:00 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	const unsigned char	*src;
	unsigned char		*dest;

	src = source;
	dest = destination;
	if (src == 0 && dest == 0)
		return (0);
	while (n > 0)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
	return (destination);
}
