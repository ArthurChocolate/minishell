/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:23:59 by tdelicia          #+#    #+#             */
/*   Updated: 2021/10/08 22:04:55 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*sdup;

	i = 0;
	while (s1[i] != '\0')
		i++;
	sdup = malloc(i + 1);
	if (sdup == 0)
		exit (errno);
	i = 0;
	while (s1[i] != '\0')
	{
		sdup[i] = s1[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
