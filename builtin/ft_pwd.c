/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:15:18 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 16:17:22 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_pwd(char **args, char **env, int *status)
{
	char	*pwd;

	args = 0;
	pwd = getcwd(NULL, 1024);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		*status = 0;
		return (env);
	}
	*status = errno;
	return (env);
}
