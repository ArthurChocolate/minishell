/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:09:16 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/16 16:57:30 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

int	ft_strlen(char *str);

static int	_ft_strlen(char *s)
{
	if (s == 0)
		return (0);
	return (ft_strlen(s));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = _ft_strlen(s1);
	j = _ft_strlen(s2);
	str = malloc(i + j + 1);
	if (str == 0)
		exit (errno);
	k = 0;
	while (k < i)
	{
		str[k] = s1[k];
		k++;
	}
	while (k < i + j)
	{
		str[k] = s2[k - i];
		k++;
	}
	str[k] = '\0';
	return (str);
}
