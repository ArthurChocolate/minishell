/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:58:23 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/17 21:43:31 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "parser/ftlst.h"

char	**env_dup(char **env);
void	free_pointerpointer(char **pathvar);
char **(*get_builtin_function(char *command)) \
			(char **args, char **env, int *status);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
void	handle_redirects(t_command *command);
void	handle_input_redirects(t_command *command, int mode);

void	exec_wait_processes(t_command *commands, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		if (i == n - 1)
		{
			waitpid(commands[i].pid, &status, 0);
			g_exit_status = WEXITSTATUS(status);
		}
		else
			waitpid(commands[i].pid, 0, 0);
		i++;
	}
	i = 0;
	while (i < n)
		close(commands[i++].pipe_fd);
}

void	fd_handler(int fdd, int i, int n, int fd[2])
{
	if (dup2(fdd, 0) == -1)
		exit(errno);
	if (i != n - 1)
		if (dup2(fd[1], 1) == -1)
			exit(errno);
	close(fd[0]);
}

void	exec_command(t_command command, char **env)
{
	char	**(*func)(char **args, char **env, int *status);
	int		status;

	func = get_builtin_function(command.args[0]);
	if (func)
	{
		func(command.args, env, &status);
		exit(status);
	}
	if (command.path)
		execve(command.path, command.args, env);
	exit(127);
}

void	pipe_and_fork(t_command *commands, int i, int fd[2])
{
	pipe(fd);
	commands[i].pid = fork();
	if (commands[i].pid == -1)
		exit(errno);
	commands[i].pipe_fd = fd[0];
}

void	exec(t_command *commands, int n, char **env)
{
	int	i;
	int	fdd;
	int	fd[2];

	fdd = 0;
	i = 0;
	while (i < n)
	{
		pipe_and_fork(commands, i, fd);
		if (commands[i].pid == 0)
		{
			fd_handler(fdd, i, n, fd);
			handle_redirects(commands + i);
			handle_input_redirects(commands + i, 0);
			exec_command(commands[i], env);
		}
		else
		{
			close(fd[1]);
			fdd = fd[0];
		}
		i++;
	}
	exec_wait_processes(commands, n);
}
