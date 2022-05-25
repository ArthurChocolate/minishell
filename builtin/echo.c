/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:22:50 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 21:38:00 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**kek_malloc(int new_len)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (new_len + 1));
	if (!new_env)
		exit(errno);
	return (new_env);
}

char	**ft_echo(char **args, char **env, int *status)
{
	bool	line_break;
	int		i;

	i = 1;
	line_break = true;
	*status = 0;
	if (!ft_strncmp(args[1], "-n", 2))
	{
		line_break = false;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (env);
}
