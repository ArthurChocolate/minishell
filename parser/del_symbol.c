/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:14:03 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/20 14:18:40 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*substr(char *str, int start, int end);
char	*ft_strdup(const char *s1);

char	*del_symbol(char *line, int i)
{
	char	*left_part;
	char	*right_part;
	char	*result;

	left_part = substr(line, 0, i - 1);
	right_part = substr(line, i + 1, ft_strlen(line) - 1);
	result = ft_strjoin(left_part, right_part);
	free(line);
	free(left_part);
	free(right_part);
	return (result);
}
