/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recvfrom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 23:25:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_recvfrom
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
 */
int ft_recvfrom(int fd, char *data, int datalen, t_sockaddr_in *saddrin) {
  int saddrin_size;
  int i;

  saddrin_size = sizeof(t_sockaddr);
  i = recvfrom(fd, data, datalen, 0, (t_sockaddr *)saddrin,
               (unsigned int *restrict) & saddrin_size);
  if (i < 0) {
    perror("recvfrom");
    // return (i);
  }
  // if (i < 0) {
  // 	ft_exit("sendto()");
  // }
  return (i);
}

/*
 * ft_recvmsg
 *
 * Description:
 *    Abstraction over recvmsg function.
 * Returns:
 *    The number of data read or -1
 */
int ft_recvmsg(int fd, char *addr, char *packet, int packetlen) {
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

  cc = recvmsg(fd, &msg, MSG_WAITALL);

  return (cc);
}
