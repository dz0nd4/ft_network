/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:10:46 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:11:02 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*element;

	if (!(element = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		element->content = (NULL);
		element->content_size = 0;
	}
	else
	{
		if (!(element->content = (void *)malloc(sizeof(void) * content_size)))
			return (NULL);
		ft_memmove(element->content, (void *)content, content_size);
		element->content_size = content_size;
	}
	element->next = (NULL);
	return (element);
}
