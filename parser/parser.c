/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:29:14 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/09 18:05:15 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_list		*syntax_split(char *line);
t_command	*split_on_commands(t_list *words, int *n_commands);
void		do_nothing(void *content);
char		*substitute_enviroment_variables(char *cmd, char **envp);
char		*find_path(char *command, char **envp);

void	redirect_substitution(t_list *redirections, char **envp)
{
	t_redirect	*redirect;

	while (redirections)
	{
		redirect = (t_redirect *)(redirections->content);
		redirect->file_name = \
			substitute_enviroment_variables(redirect->file_name, envp);
		redirections = redirections -> next;
	}
}

void	here_doc_substitution(t_list *here_docs, char **envp)
{
	char	*file_name;

	while (here_docs)
	{
		file_name = (char *)(here_docs->content);
		here_docs->content = \
			(void *)substitute_enviroment_variables(file_name, envp);
		here_docs = here_docs-> next;
	}
}

void	substitute_in_command(t_command command, char **envp)
{
	int	j;

	j = 0;
	while (command.args[j])
	{
		command.args[j] = \
			substitute_enviroment_variables(command.args[j], envp);
		j++;
	}
	redirect_substitution(command.output, envp);
	redirect_substitution(command.input, envp);
	redirect_substitution(command.output_append, envp);
	here_doc_substitution(command.here_doc, envp);
}

t_command	*parse(char *line, int *n, char **envp)
{
	t_list		*words;
	t_command	*commands;
	int			i;

	words = syntax_split(line);
	commands = split_on_commands(words, n);
	if (commands == 0)
	{
		printf("parsing error\n");
		ft_lstclear(&words, &free);
		return (0);
	}
	ft_lstclear(&words, &do_nothing);
	i = 0;
	while (i < *n)
	{
		substitute_in_command(commands[i], envp);
		if (commands[i].args[0] != 0)
			commands[i].path = find_path(commands[i].args[0], envp);
		i++;
	}
	return (commands);
}

/*int	main(int argc, char **argv, char **envp)
{
	int n;
	int i;
	t_command *commands;
        
	commands = parse("cd kek", &n, envp);


	t_redirect *output_redir;
	t_list *output_lst;
	i = 0;
	if (commands)
	{
		while (i < n)
		{
			printf("--------------------\n");
			printf("COMMAND %d\n", i);
			printf("path to command: %s\n", commands[i].path);
			printf("args: | ");
			char **args;
			args = commands[i].args;
			while (*args)
			{
				printf("%s | ", *args);
				args++;
			}
			printf("\n");
			printf("output append: | ");
			output_lst = commands[i].output_append;
			while (output_lst)
			{
				output_redir = (t_redirect *)(output_lst->content);
				printf("%d %s | ", output_redir->fd, output_redir->file_name);
				output_lst = output_lst -> next;
			}
			printf("\n");
			printf("output: | ");
			output_lst = commands[i].output;
			while (output_lst)
			{
				output_redir = (t_redirect *)(output_lst->content);
				printf("%d %s | ", output_redir->fd, output_redir->file_name);
				output_lst = output_lst -> next;
			}
			printf("\n");
			printf("here doc: | ");
			output_lst = commands[i].here_doc;
			while (output_lst)
			{
				printf("%s | ", (char *)(output_lst->content));
				output_lst = output_lst -> next;
			}
			printf("\n");
			printf("input: | ");
			output_lst = commands[i].input;
			while (output_lst)
			{
				output_redir = (t_redirect *)(output_lst->content);
				printf("%s | ", output_redir->file_name);
				output_lst = output_lst -> next;
			}
			printf("\n");
			i++;
		}
		free_commands(commands, n);
		commands = 0;
	}
	getchar();
}*/
