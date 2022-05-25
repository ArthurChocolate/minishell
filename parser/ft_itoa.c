/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:13:57 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/09 18:30:59 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char	*ft_strdup(const char *s1);

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	handle_minus(char *str, int *n)
{
	if (*n < 0)
	{
		str[0] = '-';
		*n = -1 * (*n);
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		d;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(n_len(n) + 1);
	if (!str)
		exit (errno);
	str[n_len(n)] = '\0';
	i = handle_minus(str, &n);
	d = 1;
	while (n / d > 9)
		d *= 10;
	while (d > 0)
	{
		str[i] = n / d % 10 + '0';
		d /= 10;
		i ++;
	}
	return (str);
}
