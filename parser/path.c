/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:00:28 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/13 20:29:45 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	free_pointerpointer(char **pathvar);
char	*get_var(char *var, char **envp);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
char **(*get_builtin_function(char *command)) \
			(char **args, char **env, int *status);

char	*check_access(char *command, char *path)
{
	struct stat	path_stat;

	path = ft_strjoin(path, "/");
	if (path == 0)
		exit(2);
	command = ft_strjoin(path, command);
	if (command == 0)
		exit(2);
	free(path);
	if (access(command, F_OK | X_OK) == 0)
	{
		stat(command, &path_stat);
		if S_ISREG(path_stat.st_mode)
			return (command);
	}
	free(command);
	return (0);
}

void	print_error(char *command, int err)
{
	if (err != 2)
		ft_putstr_fd(strerror(err), 2);
	else
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
}

char	*find_path_in_pathvar(char *command, char **pathvar, int *err)
{
	char	*path;

	while (*pathvar)
	{
		path = check_access(command, *(pathvar++));
		if (errno != 2)
			*err = errno;
		if (path)
			return (path);
	}
	return (0);
}

char	*handle_root_path(char *command, int *err)
{
	char		*path;
	struct stat	path_stat;

	if (access(command, F_OK | X_OK) == 0)
	{
		stat(command, &path_stat);
		if (S_ISREG(path_stat.st_mode))
		{
			path = ft_strdup(command);
			if (path == 0)
				exit(2);
			return (path);
		}
		else
		{
			*err = 2;
			return (0);
		}
	}
	if (errno != 2)
		*err = errno;
	return (NULL);
}

char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**pathvar;
	int		err;
	char	**(*func)(char **args, char **env, int *status);

	func = get_builtin_function(command);
	if (func)
		return (ft_strdup(command));
	err = 2;
	path = handle_root_path(command, &err);
	if (path != 0)
		return (path);
	if (get_var("PATH", envp))
	{
		pathvar = ft_split(get_var("PATH", envp), ':');
		if (pathvar == 0)
			exit(2);
		path = find_path_in_pathvar(command, pathvar, &err);
		free_pointerpointer(pathvar);
	}
	if (path == 0)
		print_error(command, err);
	return (path);
}
