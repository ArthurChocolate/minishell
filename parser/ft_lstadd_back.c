/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:25:05 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/19 11:42:33 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}
