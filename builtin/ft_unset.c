/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:15:35 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 21:38:12 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pointerpointer(char **pathvar);
void	ft_putstr_fd(char *s, int fd);
char	**kek_malloc(int new_len);

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	is_match_var_arg(char *var, char *arg)
{
	while (*arg)
	{
		if (*var != *arg)
			return (0);
		arg++;
		var++;
	}
	if (*var == '=')
		return (1);
	else
		return (0);
}

static int	check_var_in_args(char *var, char **args)
{
	while (*args)
	{
		if (check_env_name_is_valid(*args))
			if (is_match_var_arg(var, *args))
				return (1);
		args++;
	}
	return (0);
}

void	check_args(char **args, int *status)
{
	while (*args)
	{
		if (!check_env_name_is_valid(*args))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			if (status)
				*status = 1;
		}
		args++;
	}
}

char	**ft_unset(char **args, char **env, int *status)
{
	char	**new_env;
	int		new_len;
	int		i;
	int		j;

	args++;
	if (status)
		*status = 0;
	check_args(args, status);
	i = 0;
	j = 0;
	new_len = env_len(env);
	new_env = kek_malloc(new_len);
	while (j < new_len)
	{
		if (!check_var_in_args(env[j], args))
		{
			new_env[i] = ft_strdup(env[j]);
			i++;
		}
		j++;
	}
	new_env[i] = 0;
	free_pointerpointer(env);
	return (new_env);
}
