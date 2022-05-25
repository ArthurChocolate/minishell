/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_ident.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:17:43 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/10 16:18:52 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		check_env_name_is_valid(char *s);
char	*substr(char *str, int start, int end);
void	ft_putstr_fd(char *s, int fd);

int	ft_kek(int a)
{
	if (a < 0)
		return (0);
	return (a);
}

int	check_symbol_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	find_end_indent(char *arg, int *mode)
{
	int	end_indent;

	end_indent = 0;
	while (arg[end_indent] && arg[end_indent] != '=')
	{
		if (arg[end_indent] == '+' && arg[end_indent + 1] == '=')
		{
			*mode = 1;
			break ;
		}
		end_indent++;
	}
	return (ft_kek(end_indent - 1));
}

char	*get_var_indent_for_export(char *arg, int *mode, \
		int *status, char **value)
{
	int		end_indent;
	char	*indent;

	*mode = 0;
	end_indent = find_end_indent(arg, mode);
	if (arg[end_indent + 1] == '=')
		*value = arg + end_indent + 2;
	else
		*value = arg + end_indent + 3;
	indent = substr(arg, 0, end_indent);
	if (!check_env_name_is_valid(indent))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		*status = 1;
		free(indent);
		return (0);
	}
	return (indent);
}
