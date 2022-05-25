/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:29:14 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/17 22:03:49 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

t_list	*syntax_split(char *line);
int		is_special_word(char *line);
int		ft_strlen(char *str);
int		is_output_redirect(char *line);
int		is_output_append_redirect(char *line);
int		fd_atoi(const char *str);
void	args_append(char **args, char *arg);
void	free_redirect(void *content);
void	do_nothing(void *content);
int		free_syntax_error(t_command *commands, int n);
int		calc_number_of_commands(t_list *words);
void	zero_commands(t_command *commands, int n, int n_args);

void	free_commands(t_command *commands, int n)
{
	int		i;
	char	**args;

	i = 0;
	while (i < n)
	{
		args = commands[i].args;
		while (*args)
		{
			free(*args);
			args++;
		}
		free(commands[i].args);
		free(commands[i].path);
		if (commands[i].input)
			ft_lstclear(&(commands[i].input), &free_redirect);
		if (commands[i].here_doc)
			ft_lstclear(&(commands[i].here_doc), &free);
		if (commands[i].output_append)
			ft_lstclear(&(commands[i].output_append), &free_redirect);
		if (commands[i].output)
			ft_lstclear(&(commands[i].output), &free_redirect);
		i++;
	}
	free(commands);
}

int	check_error(t_list *words, t_command *commands, int *n_commands)
{
	char		*word;

	word = (char *)(words->content);
	if (is_special_word(word) && word[0] != '|')
	{
		if (words->next == 0 || is_special_word((char *)(words->next->content)))
		{
			free_syntax_error(commands, *n_commands);
			return (1);
		}
	}
	if (word[0] == '|')
	{
		if (words->next == 0 || ((char *)(words->next->content))[0] == '|')
		{
			free_syntax_error(commands, *n_commands);
			return (1);
		}
	}
	return (0);
}

void	add_redirect(t_list **words, t_list **redirections, int mode)
{
	char		*word;
	t_redirect	*redir;

	word = (char *)((*words)->content);
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		exit(errno);
	redir->fd = fd_atoi(word);
	redir->saved_fd = -1;
	redir->mode = mode;
	redir->file_name = (char *)((*words)->next->content);
	ft_lstadd_back(redirections, ft_lstnew(redir));
	free((*words)->content);
	(*words)->content = 0;
	(*words) = (*words)->next;
}

void	word_handler(t_command *commands, t_list **words, int *i)
{
	char		*word;

	word = (char *)((*words)->content);
	if (is_output_append_redirect(word))
		add_redirect(words, &(commands[*i].output), 1);
	else if (is_output_redirect(word))
		add_redirect(words, &(commands[*i].output), 0);
	else if (word[0] == '<' && word[1] == '<')
		add_redirect(words, &(commands[*i].input), 1);
	else if (word[0] == '<')
		add_redirect(words, &(commands[*i].input), 0);
	else if (word[0] == '|')
	{
		(*i)++;
		free((*words)->content);
		(*words)->content = 0;
	}
	else
		args_append(commands[*i].args, (char *)((*words)->content));
}

t_command	*split_on_commands(t_list *words, int *n_commands)
{
	t_command	*commands;
	int			i;
	t_list		*words_;

	words_ = words;
	*n_commands = calc_number_of_commands(words) + 1;
	commands = malloc(sizeof(t_command) * (*n_commands));
	if (!commands)
		exit(errno);
	zero_commands(commands, *n_commands, ft_lstsize(words));
	i = 0;
	while (words)
	{
		if (check_error(words, commands, n_commands))
			return (0);
		word_handler(commands, &words, &i);
		words = words->next;
	}
	return (commands);
}
