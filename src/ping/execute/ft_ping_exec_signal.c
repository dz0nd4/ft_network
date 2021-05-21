/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_exec_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 13:48:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void 	ft_ping_exec_sigint(int signo)
{
	// free(g_pg.sock.pckt);

	ft_ping_exec_stats(g_pg.stats);
	exit(0);
}

void 	ft_ping_exec_sigarlm(int signo)
{
	// printf("hello there\n");
	// alarm(1);
	ft_ping_exec_send(&g_pg.sock, g_pg.opts, &g_pg.stats);
	alarm(1);
}