/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_commands_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:09:22 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 15:57:36 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fd_atoi(const char *str)
{
	long int	n;

	if (!(*str >= '0' && *str <= '9'))
		return (1);
	n = 0;
	while (*str >= '0' && *str <= '9')
	{
		n *= 10;
		n += (*str - '0');
		if (n > 2147483647)
			return (-1);
		str++;
	}
	return (n);
}

void	args_append(char **args, char *arg)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	args[i] = arg;
}

void	free_redirect(void *content)
{
	t_redirect	*t;

	t = (t_redirect *)content;
	free(t->file_name);
	free(t);
}

void	do_nothing(void *content)
{
	(void)content;
}

int	free_syntax_error(t_command *commands, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(commands[i].args);
		if (commands[i].input)
			ft_lstclear(&(commands[i].input), &free);
		if (commands[i].here_doc)
			ft_lstclear(&(commands[i].here_doc), &do_nothing);
		if (commands[i].output_append)
			ft_lstclear(&(commands[i].output_append), &free);
		if (commands[i].output)
			ft_lstclear(&(commands[i].output), &free);
		i++;
	}
	free(commands);
	return (1);
}
