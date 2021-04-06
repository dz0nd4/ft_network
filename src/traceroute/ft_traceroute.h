/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:13:24 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h> 

# include "../ft_network_global.h"

#define DEFAULT_DATA_SIZE      32       // default data size
#define DEFAULT_RECV_TIMEOUT   6000     // six second
#define DEFAULT_TTL            30       // default timeout
#define BUF_SIZE 1024

// Global variables

// int   gAddressFamily = AF_UNSPEC,         // Address family to use
//       gProtocol      = IPPROTO_ICMP,      // Protocol value
//       gTtl           = DEFAULT_TTL,       // Default TTL value
//       gTimeout       = DEFAULT_RECV_TIMEOUT; // Amount of data to send
// int  bResolve       = 1;              // Resolve addresses to host names

// char *gDestination   = NULL;              // Destination

// /**/

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct		s_traceroute
{
  const char  *target_ipv4;
  int         hops;
  int         byte_packets;
  IN_ADDR     in_addr;
  SOCKET      sock_udp;
  SOCKET      sock_icmp;
  SOCKADDR_IN addr_in_to;
}					t_trace;

int			ft_traceroute(int argc, const char *argv[]);

int			ft_traceroute_init(t_trace *ctx, const char *ipv4);

void 	  ft_exit(char *s);

#endif
