/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:53:22 by tdelicia          #+#    #+#             */
/*   Updated: 2022/04/19 08:32:51 by tdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftlst.h"
#include <errno.h>
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (!root)
		exit (errno);
	root -> content = content;
	root -> next = 0;
	return (root);
}
