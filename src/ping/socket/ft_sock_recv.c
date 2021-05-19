/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_recv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:47:57 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

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
