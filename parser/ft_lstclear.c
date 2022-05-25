/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:36:48 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/23 13:44:23 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (*lst == 0)
		return ;
	temp = *lst;
	while (temp -> next)
	{
		temp2 = temp;
		temp = temp -> next;
		(*del)(temp2 -> content);
		free(temp2);
	}
	(*del)(temp -> content);
	free(temp);
	*lst = 0;
}
