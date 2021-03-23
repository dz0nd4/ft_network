/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:10:41 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:10:58 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;
	t_list	*element;
	t_list	*tmp;

	if (!(element = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	element = f(lst);
	first = element;
	tmp = lst->next;
	while (tmp)
	{
		if (!(new = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		new = f(tmp);
		element->next = new;
		element = element->next;
		tmp = tmp->next;
		new = NULL;
	}
	return (first);
}
