/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naqua <naqua@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:16:33 by naqua             #+#    #+#             */
/*   Updated: 2022/05/17 18:15:56 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../parser/command.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

int		g_exit_status;

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	signal_ctrl_c(int code);
void	ft_signal(void);
void	signal_ctrl_c_child(int code);
void	ft_signal_child(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		check_env_name_is_valid(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	**ft_env(char **args, char **env, int *status);
char	**ft_cd(char **args, char **env, int *status);
char	**ft_unset(char **args, char **env, int *status);
char	**ft_export(char **args, char **env, int *status);
char	**ft_unset_for_export(char **args, char **env);
char	**ft_echo(char **args, char **env, int *status);
void	ft_signal_here_doc(void);

#endif
