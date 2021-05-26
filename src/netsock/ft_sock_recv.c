/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_recv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 23:25:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_sock_recv
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
*/
int    ft_sock_recv(int fd, char *data, int datalen, t_sockaddr_in *saddrin)
{
	int saddrin_size;
	int i;

	saddrin_size = sizeof(t_sockaddr);
	i = recvfrom(fd, data, datalen, 0, (t_sockaddr *)saddrin, &saddrin_size);
	if (i < 0) {
        perror("recvfrom");
		return (-1);
    }
	// if (i < 0) {
	// 	ft_exit("sendto()");
	// }
	return (i);
}

/*
 * ft_sock_recvmsg
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
*/
int     ft_sock_recvmsg(int sfd, char *addr, char *packet, int packetlen)
{
    t_iovec iov;
    t_msghdr msg;
    int cc;

    ft_memset(&iov, 0, sizeof(iov));
    ft_memset(&msg, 0, sizeof(msg));

    iov.iov_base = packet;
    iov.iov_len = packetlen;
    msg.msg_name = addr;
    msg.msg_namelen = FT_ADDRSTRLEN;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    cc = recvmsg(sfd, &msg, MSG_WAITALL);
    if (cc < 0)
        return (-1);
    return (cc);
}
