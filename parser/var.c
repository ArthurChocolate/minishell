/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:58:13 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/10 13:29:48 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

extern int	g_exit_status;
int			ft_strlen(char *str);
char		*ft_itoa(int n);

int	str_start_with(char *str, char *start_str)
{
	int	i;

	i = 0;
	while (start_str[i])
	{
		if (str[i] != start_str[i])
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

char	*get_var(char *var, char **envp)
{
	if (var == 0)
		return (0);
	if (var[0] == '?')
		return (ft_itoa(g_exit_status) - 1);
	while (*envp)
	{
		if (str_start_with(*envp, var))
			return (*envp + ft_strlen(var));
		envp++;
	}
	return (0);
}
