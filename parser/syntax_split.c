/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:16:45 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/20 15:00:25 by tdelicia         ###   ########.fr       */
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
void	redirect_output_append_handle(char *line, \
		t_split_data *data, t_list **result);
void	redirect_output_handle(char *line, t_split_data *data, \
		t_list **result);
void	pipe_and_redirect_input_handle(char *line, \
		t_split_data *data, t_list **result);
void	here_doc_handle(char *line, t_split_data *data, t_list **result);

int	change_state(int *state, char *line, int *i)
{
	if (*state == OUTSIDE_QUOTES && line[*i] == '"')
	{
		*state = IN_DOUBLE_QUOTES;
		*i = (*i) + 1;
		return (1);
	}
	if (*state == OUTSIDE_QUOTES && line[*i] == '\'')
	{
		*state = IN_SINGLE_QUOTES;
		*i = (*i) + 1;
		return (1);
	}
	if (*state == IN_SINGLE_QUOTES && line[*i] == '\'')
	{
		*state = OUTSIDE_QUOTES;
		*i = (*i) + 1;
		return (1);
	}
	if (*state == IN_DOUBLE_QUOTES && line[*i] == '"')
	{
		*state = OUTSIDE_QUOTES;
		*i = (*i) + 1;
		return (1);
	}
	return (0);
}

void	inner_split(char *line, t_split_data *data, t_list **result)
{
	if ((line[data->i] == ' ' || line[data->i] == '\t') && data->in_word)
	{
		ft_lstadd_back(result, ft_lstnew((void *)substr(line, \
						data->start_word_index, data->i - 1)));
		data->in_word = 0;
	}
	else if (line[data->i] == '<' && line[data->i + 1] == '<')
		here_doc_handle(line, data, result);
	else if (line[data->i] == '>' && line[data->i + 1] == '>')
		redirect_output_append_handle(line, data, result);
	else if (line[data->i] == '>')
		redirect_output_handle(line, data, result);
	else if (line[data->i] == '|' || line[data->i] == '<')
		pipe_and_redirect_input_handle(line, data, result);
	else if (!data->in_word && line[data->i] != ' ' && line[data->i] != '\t')
	{
		data->in_word = 1;
		data->start_word_index = data->i;
	}
}

void	data_init(t_split_data *data)
{
	data->i = 0;
	data->state = OUTSIDE_QUOTES;
	data->in_word = 0;
}

t_list	*syntax_split(char *line)
{
	t_split_data	data;
	t_list			*result;

	data_init(&data);
	result = 0;
	while (line[data.i])
	{
		if (change_state(&(data.state), line, &(data.i)))
		{
			if (!data.in_word)
			{
				data.in_word = 1;
				data.start_word_index = data.i - 1;
			}
			continue ;
		}
		if (data.state == OUTSIDE_QUOTES)
			inner_split(line, &data, &result);
		data.i++;
	}
	if (data.in_word)
		ft_lstadd_back(&result, ft_lstnew((void *)substr(line, \
						data.start_word_index, data.i - 1)));
	return (result);
}

/*
int	main()
{
	t_list *result = syntax_split("   ");
	while (result)
	{
		char *str = (char *)(result->content);
		printf("%s\n", str);
		result = result -> next;
	}
	getchar();
}
*/
