/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:37:01 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/17 20:53:34 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stddef.h>
# include <string.h>
# include "ftlst.h"

typedef struct s_redirect
{
	int		fd;
	int		mode;
	int		file_fd;
	char	*file_name;
	int		saved_fd;
}	t_redirect;

typedef struct s_command
{
	char	**args;
	char	*path;
	int		pid;
	int		pipe_fd;
	t_list	*output;
	t_list	*output_append;
	t_list	*input;
	t_list	*here_doc;
}	t_command;

void		free_commands(t_command *commands, int n);
t_command	*parse(char *line, int *n, char **envp);
int			ft_strlen(char *str);

#endif
