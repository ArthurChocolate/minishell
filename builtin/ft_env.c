/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:16:00 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 15:30:01 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd);

char	**ft_env(char **args, char **env, int *status)
{
	char	**kek;

	kek = env;
	*status = 0;
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		*status = 1;
		return (env);
	}
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (kek);
}
