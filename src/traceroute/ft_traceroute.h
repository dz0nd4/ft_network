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
#define __USE_BSD	/* use bsd'ish ip header */
#include <sys/socket.h>	/* these headers are for a Linux system, but */
#include <netinet/in.h>	/* the names on other systems are easy to guess.. */
#include <netinet/ip.h>
#define __FAVOR_BSD	/* use bsd'ish tcp header */
#include <netinet/tcp.h>
#include <unistd.h>
#include<errno.h>
#include<time.h>

# include "../ft_network_global.h"

#define DEFAULT_DATA_SIZE      32       // default data size
#define DEFAULT_RECV_TIMEOUT   6000     // six second
#define DEFAULT_TTL            30       // default timeout
#define BUF_SIZE 1024

#define FT_ADDRSTRLEN 16

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
typedef int t_socket;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in  t_sockaddr_in;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr t_sockaddr;
typedef struct in_addr IN_ADDR;
typedef struct in_addr t_in_addr;

typedef struct		s_traceroute
{
  const char  *target_ipv4;
  char        *host_name;
  char        host_ipv4[FT_ADDRSTRLEN];
  int         hops;
  int         byte_packets;
  IN_ADDR     in_addr;
  SOCKET      sock_udp;
  SOCKET      sock_icmp;
  SOCKADDR_IN addr_in_to;
}					t_trace;

int			ft_traceroute(int argc, const char *argv[]);

int			ft_traceroute_init(t_trace *ctx, const char *ipv4);
int     ft_traceroute_send(t_trace *ctx, int port, int ttl);

void 	  ft_exit(char *s);

#endif
