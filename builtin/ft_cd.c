/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:23:12 by naqua             #+#    #+#             */
/*   Updated: 2022/05/06 16:23:13 by naqua            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_in_env(char **env, char *indent, char *value, int mode);
char	*get_var(char *var, char **envp);

char	*get_var_fixed(char *var, char **envp)
{
	char	*result;

	result = get_var(var, envp);
	if (result)
		result++;
	return (result);
}

char	**change_dir(char *path, int *status, char **env)
{
	char	*cwd;

	if (!chdir(path))
	{
		cwd = ft_strdup(get_var_fixed("PWD", env));
		env = add_in_env(env, "OLDPWD", cwd, 0);
		free(cwd);
		cwd = getcwd(NULL, 1024);
		env = add_in_env(env, "PWD", cwd, 0);
		free(cwd);
		return (env);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		if (access(path, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		else if (access(path, R_OK) == -1)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		else
			ft_putendl_fd(": Not a directory", STDERR_FILENO);
		*status = 1;
	}
	return (env);
}

char	**ft_cd(char **args, char **env, int *status)
{
	*status = 0;
	if (args)
	{
		if (!args[1])
		{
			*status = 1;
			return (env);
		}
		env = change_dir(args[1], status, env);
		return (env);
	}
	return (env);
}
