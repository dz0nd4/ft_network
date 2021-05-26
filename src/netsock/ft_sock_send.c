/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_send.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:49:21 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_socket_send
 *
 * Description:
 *    Abstraction over sendto function.
 * Returns:
 *    The number of data read or -1
*/
int    ft_sock_send(int fd, char *data, int datalen, t_sockaddr_in *saddrin)
{
	int i;

	i = sendto(fd, data, datalen, 0, (t_sockaddr *)saddrin, sizeof(t_sockaddr));
	if (i <= 0) {
		// perror("sendto");
		return (FT_EXFAIL);
	}
	// if (i < 0) {
	// 	ft_exit("sendto()");
	// }
	return (FT_EXOK);
}
