/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:10:26 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:10:49 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*after;
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		after = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = after;
	}
	*alst = (NULL);
}
