/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_for_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:15:43 by naqua             #+#    #+#             */
/*   Updated: 2022/05/06 15:15:44 by naqua            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pointerpointer(char **pathvar);

static int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	is_match_var_arg(char *var, char *arg)
{
	while (*arg != '=')
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

static int	char_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	check_var_in_args(char *var, char **args)
{
	while (*args)
	{
		if (char_in_str(*args, '=') && is_match_var_arg(var, *args))
			return (1);
		args++;
	}
	return (0);
}

char	**ft_unset_for_export(char **args, char **env)
{
	char	**new_env;
	int		new_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_len = env_len(env) + env_len(args);
	new_env = malloc(sizeof(char *) * new_len);
	if (!new_env)
		exit(12);
	while (j < env_len(env))
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
