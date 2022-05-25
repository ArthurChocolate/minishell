/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:28:28 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/24 15:37:39 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strlen(char *str);

int	is_special_word(char *line)
{
	char	c;

	c = line[ft_strlen(line) - 1];
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_output_append_redirect(char *line)
{
	int	l;

	l = ft_strlen(line);
	if (l > 1 && line[l - 1] == '>' && line[l - 2] == '>')
		return (1);
	return (0);
}

int	is_output_redirect(char *line)
{
	int	l;

	l = ft_strlen(line);
	if (line[l - 1] == '>')
		return (1);
	return (0);
}
