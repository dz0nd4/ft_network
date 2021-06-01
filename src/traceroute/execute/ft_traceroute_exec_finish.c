/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_init.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:55:01 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int 	ft_traceroute_exec_finish_to(t_trace *tr, t_tr_sock *to)
{
  close(to->fd);
  free(to->data);

	return (FT_EXOK);
}

int 	ft_traceroute_exec_finish_from(t_tr_opts *opts, t_tr_sock *from)
{
  close(from->fd);
  free(from->data);

	return (FT_EXOK);
}
