/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:54:43 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/09 18:39:25 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTSIDE_QUOTES 0
#define IN_SINGLE_QUOTES 1
#define IN_DOUBLE_QUOTES 2

int		ft_strlen(char *str);
char	*get_var(char *var, char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	*substr(char *str, int start, int end);
char	*ft_strdup(const char *s1);
char	*del_symbol(char *line, int i);

int	change_state_parser(int *state, char *line, int *i)
{
	if (*state == OUTSIDE_QUOTES && line[*i] == '"')
	{
		*state = IN_DOUBLE_QUOTES;
		return (1);
	}
	if (*state == OUTSIDE_QUOTES && line[*i] == '\'')
	{
		*state = IN_SINGLE_QUOTES;
		return (1);
	}
	if (*state == IN_SINGLE_QUOTES && line[*i] == '\'')
	{
		*state = OUTSIDE_QUOTES;
		return (1);
	}
	if (*state == IN_DOUBLE_QUOTES && line[*i] == '"')
	{
		*state = OUTSIDE_QUOTES;
		return (1);
	}
	return (0);
}

int	len_variable(char *line)
{
	int		j;

	if (line[0] == '?')
		return (1);
	j = 0;
	while ((line[j] >= 'A' && line[j] <= 'Z')
		|| (line[j] >= 'a' && line[j] <= 'z')
		|| (line[j] == '_')
		|| (line[j] >= '1' && line[j] <= '9'))
		j++;
	return (j);
}

char	*substitute_variable(char *line, int *i, char **envp)
{
	char	*str;
	int		len_var;
	char	*result_line;
	char	*str2;

	len_var = len_variable(line + *i + 1);
	result_line = substr(line, 0, *i - 1);
	str = substr(line, *i, *i + len_var);
	str2 = get_var(str + 1, envp);
	free(str);
	if (str2)
	{
		str2++;
		str = ft_strjoin(result_line, str2);
		free(result_line);
		result_line = str;
	}
	str = str2;
	str2 = substr(line, *i + len_var + 1, ft_strlen(line));
	*i = *i + ft_strlen(str);
	str = ft_strjoin(result_line, str2);
	free(str2);
	free(result_line);
	return (str);
}

char	*substitute_enviroment_variables(char *cmd, char **envp)
{
	int		i;
	int		state;
	char	*line;

	i = 0;
	state = OUTSIDE_QUOTES;
	line = cmd;
	while (line[i])
	{
		if (change_state_parser(&state, line, &i))
			line = del_symbol(line, i);
		else if (line[i] == '$' && \
				((line[i + 1] >= 'A' && line[i + 1] <= 'Z') || \
				(line[i + 1] >= 'a' && line[i + 1] <= 'z') || \
				(line[i + 1] == '_') || (line[i + 1] == '?') \
				) && (state == OUTSIDE_QUOTES || state == IN_DOUBLE_QUOTES))
		{
			cmd = substitute_variable(line, &i, envp);
			free(line);
			line = cmd;
		}
		else
			i++;
	}
	return (line);
}

/*
int	main(int argc, char **argv, char **envp)
{
	char	str[] = "'asd $SHLVL' \"$PATH\"lfj";
	char	*line;

	line = substitute_enviroment_variables(str, envp);
	printf("%s\n", line);
	getchar();
}
*/
