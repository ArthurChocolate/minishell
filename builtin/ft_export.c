/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:15:49 by naqua             #+#    #+#             */
/*   Updated: 2022/05/10 16:33:00 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	*ft_strdup(const char *s1);
char	*get_var_indent_for_export(char *arg, \
		int *mode, int *status, char **value);
char	*ft_strjoin(char *s1, char *s2);
char	*get_var(char *var, char **envp);
int		env_len(char **env);
int		is_match_var_arg(char *var, char *arg);
void	free_pointerpointer(char **pathvar);
char	*ft_strdup(const char *s1);

char	**unset_var(char **env, char *indent)
{
	char	**new_env;
	int		len;
	int		i;
	char	**en;

	en = env;
	i = 0;
	len = env_len(env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		exit(errno);
	while (*env)
	{
		if (!is_match_var_arg(*env, indent))
		{
			new_env[i] = ft_strdup(*env);
			i++;
		}
		env++;
	}
	new_env[i] = 0;
	free_pointerpointer(en);
	return (new_env);
}

char	*env_join(char *indent, char *value, char *current_value, int mode)
{
	char	*tmp;
	char	*res;

	if (mode)
	{
		res = ft_strjoin(indent, "=");
		tmp = res;
		res = ft_strjoin(res, current_value);
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, value);
		free(tmp);
	}
	else
	{
		res = ft_strjoin(indent, "=");
		tmp = res;
		res = ft_strjoin(res, value);
		free(tmp);
	}
	return (res);
}

char	**add_in_env(char **env, char *indent, char *value, int mode)
{
	char	*current_value;
	int		i;

	current_value = 0;
	if (get_var(indent, env))
		current_value = ft_strdup(get_var(indent, env) + 1);
	env = unset_var(env, indent);
	i = 0;
	while (env[i])
		i++;
	env[i] = env_join(indent, value, current_value, mode);
	env[i + 1] = 0;
	free(current_value);
	return (env);
}

char	**ft_export(char **args, char **env, int *status)
{
	int		mode;
	char	*indent;
	char	*value;

	*status = 0;
	args++;
	while (*args)
	{
		indent = get_var_indent_for_export(*args, &mode, status, &value);
		if (indent)
			env = add_in_env(env, indent, value, mode);
		free(indent);
		args++;
	}
	return (env);
}
