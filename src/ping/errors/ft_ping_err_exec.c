/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_err_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/20 16:11:31 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int  ft_ping_error_host(const char *dst)
{
	fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", dst);
	return(FT_EXFAIL);
}

int     ft_ping_err_exec_recv(const char *err)
{
	fprintf(stderr, "ping: receive: %s\n", err);
	return(FT_EXFAIL);
}