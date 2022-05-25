/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:09:36 by naqua             #+#    #+#             */
/*   Updated: 2022/05/11 16:09:37 by naqua            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	calc_number_of_commands(t_list *words)
{
	int	i;

	i = 0;
	while (words)
	{
		if (((char *)words->content)[0] == '|')
			i++;
		words = words->next;
	}
	return (i);
}

void	zero_commands(t_command *commands, int n, int n_args)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		commands[i].args = malloc(sizeof(char *) * n_args + 1);
		if (!commands[i].args)
			exit(errno);
		j = 0;
		while (j < n_args + 1)
		{
			commands[i].args[j] = 0;
			j++;
		}
		commands[i].path = 0;
		commands[i].output = 0;
		commands[i].output_append = 0;
		commands[i].input = 0;
		commands[i].here_doc = 0;
		i++;
	}
}
