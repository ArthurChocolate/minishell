/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:22:26 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 22:23:12 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_redirects(t_command *command);
char	**env_dup(char **env);
void	free_pointerpointer(char **pathvar);
char **(*get_builtin_function(char *command)) \
			(char **args, char **env, int *status);
int		ft_strcmp(char *s1, char *s2);
void	exec(t_command *commands, int n, char **env);
void	handle_input_redirects(t_command *command, int mode);
void	print_file_error(t_redirect *redirect, int exit);
int		open_file_builtin(t_redirect *redirect);

int	handle_redirects_builtin(t_command *command)
{
	t_list		*output_lst;
	t_redirect	*redirect;

	output_lst = (t_list *)command->output;
	while (output_lst)
	{
		redirect = (t_redirect *)output_lst->content;
		if (open_file_builtin(redirect) == 0)
			return (0);
		redirect->saved_fd = dup(redirect->fd);
		if (dup2(redirect->file_fd, redirect->fd) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		output_lst = output_lst-> next;
	}
	return (1);
}

void	restor_fds(t_command *command)
{
	t_list		*output_lst;
	t_redirect	*redirect;

	output_lst = (t_list *)command->output;
	while (output_lst)
	{
		redirect = (t_redirect *)output_lst->content;
		if (redirect->saved_fd != -1)
		{
			if (dup2(redirect->saved_fd, redirect->fd) == -1)
				exit(errno);
			close(redirect->saved_fd);
		}
		output_lst = output_lst -> next;
	}
}

char	**exec_commands(t_command *commands, int n, char **env)
{
	char	**(*func)(char **args, char **env, int *status);
	int		pid;
	int		status;

	func = get_builtin_function(commands[0].args[0]);
	if (func && n == 1)
	{
		pid = fork();
		if (pid == -1)
			exit(errno);
		if (pid == 0)
			handle_input_redirects(commands, 1);
		else
		{
			waitpid(pid, &status, 0);
			g_exit_status = status;
			if (handle_redirects_builtin(commands) && status == 0)
				env = func(commands[0].args, env, &g_exit_status);
			restor_fds(commands);
		}
	}
	else
		exec(commands, n, env);
	free_commands(commands, n);
	return (env);
}

char	**init(int argc, char **argv, char **env)
{
	argc = 0;
	argv = 0;
	g_exit_status = 0;
	env = env_dup(env);
	ft_signal();
	return (env);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	int			n;
	t_command	*commands;

	env = init(argc, argv, env);
	while (1)
	{
		input = readline("minishell>");
		if (!input)
			exit(0);
		add_history(input);
		commands = parse(input, &n, env);
		ft_signal_child();
		if (commands != 0)
			env = exec_commands(commands, n, env);
		ft_signal();
		free(input);
	}
}
