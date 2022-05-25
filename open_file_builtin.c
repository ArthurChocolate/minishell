/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:22:10 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/17 22:22:35 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	print_file_error(t_redirect *redirect, int exit);

int	open_file_builtin(t_redirect *redirect)
{
	if (redirect->mode)
	{
		redirect->file_fd = open((redirect->file_name), \
			O_RDWR | O_APPEND | O_CREAT, 0666);
		if (redirect->file_fd == -1)
		{
			print_file_error(redirect, 0);
			return (0);
		}
	}
	else
	{
		redirect->file_fd = open((redirect->file_name), \
			O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (redirect->file_fd == -1)
		{
			print_file_error(redirect, 0);
			return (0);
		}
	}
	return (1);
}
