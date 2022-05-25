/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:06:40 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/17 22:15:13 by tdelicia         ###   ########.fr       */
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
void	ft_putstr_fd(char *s, int fd);

void	print_file_error(t_redirect *redirect, int exit_)
{
	ft_putstr_fd(redirect->file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (exit_)
		exit(1);
}

void	open_file(t_redirect *redirect)
{
	if (redirect->mode)
	{
		redirect->file_fd = open((redirect->file_name), \
				O_RDWR | O_APPEND | O_CREAT, 0666);
		if (redirect->file_fd == -1)
			print_file_error(redirect, 1);
	}
	else
	{
		redirect->file_fd = open((redirect->file_name), \
				O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (redirect->file_fd == -1)
			print_file_error(redirect, 1);
	}
}

void	handle_redirects(t_command *command)
{
	t_list		*output_lst;
	t_redirect	*redirect;

	output_lst = (t_list *)command->output;
	while (output_lst)
	{
		redirect = (t_redirect *)output_lst->content;
		open_file(redirect);
		if (dup2(redirect->file_fd, redirect->fd) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(errno);
		}
		output_lst = output_lst-> next;
	}
}

void	here_doc_handler(t_list *redir_lst, t_redirect *redirect)
{
	int			fd[2];
	char		*input;

	ft_signal_here_doc();
	pipe(fd);
	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, redirect->file_name) || input == 0)
		{
			free(input);
			close(fd[1]);
			break ;
		}
		ft_putstr_fd(input, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(input);
	}
	if (redir_lst->next == 0)
		if (dup2(fd[0], 0) == -1)
			exit(errno);
	ft_signal();
}

void	handle_input_redirects(t_command *command, int mode)
{
	t_list		*redir_lst;
	t_redirect	*redirect;

	redir_lst = (t_list *)command->input;
	while (redir_lst)
	{
		redirect = (t_redirect *)redir_lst->content;
		if (redirect->mode)
			here_doc_handler(redir_lst, redirect);
		else
		{
			redirect->file_fd = open((redirect->file_name), O_RDONLY);
			if (redirect->file_fd == -1)
				print_file_error(redirect, 1);
			if (dup2(redirect->file_fd, 0) == -1)
				exit(errno);
		}
		redir_lst = redir_lst-> next;
	}
	if (mode)
		exit(0);
}
