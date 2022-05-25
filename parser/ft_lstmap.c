/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:57:12 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/19 08:32:30 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftlst.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_lst;
	t_list	*f_elem;

	f_lst = 0;
	while (lst)
	{
		f_elem = ft_lstnew((*f)(lst -> content));
		if (f_elem == 0)
		{
			ft_lstclear(&f_lst, del);
			return (0);
		}
		ft_lstadd_back(&f_lst, f_elem);
		lst = lst -> next;
	}
	return (f_lst);
}
