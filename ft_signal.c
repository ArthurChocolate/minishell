/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:42:42 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 18:16:05 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	signal_ctrl_c(int code)
{
	(void)code;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
}

void	signal_ctrl_c_child(int code)
{
	(void)code;
}

void	ft_signal_child(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c_child);
}

void	ft_signal_here_doc(void)
{
	signal(SIGINT, exit);
}
