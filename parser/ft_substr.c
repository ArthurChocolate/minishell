/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:23:07 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/19 14:26:02 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

void	*ft_memcpy(void *destination, const void *source, size_t n);

char	*substr(char *str, int start, int end)
{
	char	*substr;

	substr = malloc(end - start + 2);
	if (substr == 0)
		exit(errno);
	ft_memcpy(substr, str + start, end - start + 1);
	substr[end - start + 1] = '\0';
	return (substr);
}
