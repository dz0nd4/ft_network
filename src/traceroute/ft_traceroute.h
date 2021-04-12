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
# include <sys/time.h>
# include <sys/types.h>

# include <time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <errno.h> 
# include <netdb.h>

# include "../ft_network_global.h"

#define DEFAULT_DATA_SIZE      32       // default data size
#define DEFAULT_RECV_TIMEOUT   6000     // six second
#define DEFAULT_TTL            30       // default timeout
#define BUF_SIZE 1024

# define FT_ADDRSTRLEN 16
# define FT_PORT_DEFAULT  33435

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

typedef struct timeval t_timeval;


typedef struct		s_traceroute
{
  char        *host_name;
  char        host_ipv4[FT_ADDRSTRLEN];
  const char  *target_ipv4;
  t_socket    sock_udp;
  t_socket    sock_icmp;
  int         hops;
  int         byte_packets;
  t_sockaddr_in from;
  char        last_addr[FT_ADDRSTRLEN];
  t_sockaddr_in to;
  t_timeval   tv;
}					t_trace;

int			ft_traceroute(int argc, const char *argv[]);

int			ft_traceroute_init(t_trace *ctx, const char *ipv4);
int     ft_traceroute_send(t_trace *ctx, int port, int ttl);
// int     ft_traceroute_receive(t_trace *ctx, int ttl);
int     ft_traceroute_receive(t_trace *ctx, int ttl);
int     ft_traceroute_print(t_trace *ctx, int ttl, int probe, int cc);

/*
 *  Errors
*/

int			ft_traceroute_help();
int			ft_traceroute_perm();
void 	  ft_exit(char *s);
void    ft_traceroute_exit(char *s);

#endif
