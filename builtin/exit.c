/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:07:56 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:07 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../includes/minishell.h"

static int	exit_atoi_error_check(long long int *n, char *str, int sign)
{
	if (*n >= LLONG_MAX / 10 && sign == 1 && *str > '7')
		return (1);
	if (*n > LLONG_MAX / 10)
		return (1);
	if (*n >= LLONG_MAX / 10 && sign == -1 && *str > '8')
		return (1);
	if (!(*str >= '0' && *str <= '9'))
		return (1);
	return (0);
}

static int	exit_atoi(char *str, long long int *n)
{
	int	sign;
	int	kek;

	sign = 1;
	*n = 0;
	kek = 0;
	if (*str == '-' && str++)
		sign = -1;
	while (*str)
	{
		if (exit_atoi_error_check(n, str, sign))
			return (0);
		if (*n >= LLONG_MAX / 10 && sign == -1 && *str == '8')
			kek = -1;
		*n *= 10;
		*n += *str - '0';
		if (kek)
			*n -= 1;
		str++;
	}
	*n *= sign;
	*n += kek;
	return (1);
}

char	**ft_exit(char **args, char **env, int *status)
{
	long long int	exit_status;

	*status = 0;
	if (!args[1])
		exit(0);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		*status = 1;
		return (env);
	}
	if (exit_atoi(args[1], &exit_status))
		exit(((unsigned long long int)exit_status) % 256);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
	return (env);
}
