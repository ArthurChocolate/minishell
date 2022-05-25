/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:37:01 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/24 14:49:45 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLST_H
# define FTLST_H

# include <stddef.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_lstsize(t_list *lst);

#endif
