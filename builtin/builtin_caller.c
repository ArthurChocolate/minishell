/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builin_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:41:02 by tdelicia          #+#    #+#             */
/*   Updated: 2022/05/13 20:31:02 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2);
char	**ft_unset(char **args, char **env, int *status);
char	**ft_export(char **args, char **env, int *status);
char	**ft_cd(char **args, char **env, int *status);
char	**ft_env(char **args, char **env, int *status);
char	**ft_echo(char **args, char **env, int *status);
char	**ft_pwd(char **args, char **env, int *status);
char	**ft_exit(char **args, char **env, int *status);

char	**(*get_builtin_function(char *command))\
(char **args, char **env, int *status)
{
	if (ft_strcmp(command, "unset"))
		return (ft_unset);
	if (ft_strcmp(command, "export"))
		return (ft_export);
	if (ft_strcmp(command, "cd"))
		return (ft_cd);
	if (ft_strcmp(command, "env"))
		return (ft_env);
	if (ft_strcmp(command, "echo"))
		return (ft_echo);
	if (ft_strcmp(command, "exit"))
		return (ft_exit);
	if (ft_strcmp(command, "pwd"))
		return (ft_pwd);
	return (0);
}
