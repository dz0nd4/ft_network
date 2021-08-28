/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_netutils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:08:53 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NETUTILS_H
#define FT_NETUTILS_H

#include "../ft_net_global.h"
#include "./pckt/ft_pckt.h"
#include "./socket/ft_socket.h"
#include "./tools/ft_tools.h"

#define FT_NI_MAXHOST 1025
#define FT_ADDRSTRLEN 16

/* TOLIB */

#define FT_UINT8_MAX 0xFF    /* 255 */
#define FT_UINT16_MAX 0xFFFF /* 65535 */

typedef struct s_arg {
  int i;
  int c;
  const char **v;
} t_arg;

typedef struct s_map_istr {
  int key;
  char *value;
} t_map_istr;

/*
  GLOBAL
*/

#define FT_PING_HDR (FT_IPHDR_LEN + FT_ICMPHDR_LEN)
#define FT_TRACE_HDR (FT_IPHDR_LEN + FT_UDPHDR_LEN)

#define FT_SOL_SOCKET SOL_SOCKET
#define FT_AI_CANONNAME 0x0002 /* Request for canonical name.  */
#define FT_NI_NUMERICHOST 1    /* Don't try to look up hostname.  */
#define FT_NI_NUMERICSERV 2    /* Don't convert port number to name.  */
#define FT_NI_NOFQDN 4         /* Only return nodename portion.  */
#define FT_NI_NAMEREQD 8       /* Don't return numeric addresses.  */
#define FT_NI_DGRAM 16         /* Look up UDP service rather than TCP.  */

#endif
