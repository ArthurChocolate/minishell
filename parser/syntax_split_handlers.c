/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_split_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:11:49 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/19 15:24:08 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ftlst.h"

#define OUTSIDE_QUOTES 0
#define IN_SINGLE_QUOTES 1
#define IN_DOUBLE_QUOTES 2

typedef struct s_split_data
{
	int	i;
	int	state;
	int	in_word;
	int	start_word_index;
}	t_split_data;

char	*substr(char *str, int start, int end);

int	is_digits(char *line, int i, int end)
{
	if (line[0] == '\0')
		return (0);
	while (i <= end)
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	here_doc_handle(char *line, t_split_data *data, t_list **result)
{
	if (data->in_word)
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i - 1)));
	ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
					data->i, data->i + 1)));
	data->in_word = 0;
	data->i++;
}

void	redirect_output_append_handle(char *line, \
		t_split_data *data, t_list **result)
{
	if (data->in_word && is_digits(line, \
				data->start_word_index, data->i - 1))
	{
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i + 1)));
	}
	else if (data->in_word)
	{
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i - 1)));
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->i, data->i + 1)));
	}
	else
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->i, data->i + 1)));
	data->in_word = 0;
	data->i++;
}

void	redirect_output_handle(char *line, t_split_data *data, \
		t_list **result)
{
	if (data->in_word && is_digits(line, \
				data->start_word_index, data->i - 1))
	{
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i)));
	}
	else if (data->in_word)
	{
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i - 1)));
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->i, data->i)));
	}
	else
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->i, data->i)));
	data->in_word = 0;
}

void	pipe_and_redirect_input_handle(char *line, \
		t_split_data *data, t_list **result)
{
	if (data->in_word)
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i - 1)));
	ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
					data->i, data->i)));
	data->in_word = 0;
}
