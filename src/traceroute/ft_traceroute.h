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



typedef int t_socket;
typedef struct sockaddr_in  t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct in_addr t_in_addr;
typedef struct addrinfo t_addrinfo;

typedef struct timeval t_timeval;

typedef struct    s_tr_time
{
  t_timeval start;
  t_timeval stop;
}                 t_tr_time;

typedef struct    s_tr_sock
{
  int   udp;
  int   icmp;
}                 t_tr_sock;

typedef struct    s_tr_host
{
  char  *name;
  char  ip[FT_ADDRSTRLEN];
  char  ip_last[FT_ADDRSTRLEN];
}                 t_tr_host;

typedef struct    s_tr_args
{
  int   hops;
  int   hops_max;
  int   probes;
  int   probes_max;
  int   byte_packets;
}                 t_tr_args;

typedef struct		s_traceroute
{
  int         argi;
  t_tr_sock   sock;
  t_tr_time   time;
  t_tr_host   host;
  t_tr_args   args;
  char        *host_name;
  char        host_ipv4[FT_ADDRSTRLEN];
  const char  *target_ipv4;
  int         hops;
  int         byte_packets;
  t_sockaddr_in from;
  char        last_addr[FT_ADDRSTRLEN];
  t_sockaddr_in to;
  t_timeval   tv;
}					t_trace;

typedef int   t_tr_ft_arg(t_trace *ctx, char *arg);

/*
 *  Arguments
*/

typedef enum			e_tr_arg_key
{
	FT_TR_ARG_F,
	FT_TR_ARG_M,
	FT_TR_ARG_Q,
	FT_TR_ARG_W,
	FT_TR_ARG_MAX
}						t_tr_arg_key;

typedef struct			s_tr_arg_dispatch
{
	t_tr_arg_key		arg_key;
	char				    *arg_name;
	t_tr_ft_arg	    *arg_dist;
}						t_tr_arg_d;

int			ft_traceroute(int argc, const char *argv[]);

int			ft_traceroute_init(t_trace *ctx, const char *ipv4);
int			ft_traceroute_args(t_trace *ctx, int argc, const char *argv[]);

int     ft_traceroute_send(t_trace *ctx);
// int     ft_traceroute_receive(t_trace *ctx, int ttl);
int     ft_traceroute_receive(t_trace *ctx);
int     ft_traceroute_print(t_trace *ctx, int cc);

/*
 *  Errors
*/

int			ft_traceroute_help(char *prgm);
int			ft_traceroute_perm();
void 	  ft_exit(char *s);
void    ft_traceroute_exit(char *s);
int 	  ft_tr_error_bad_opt(t_trace *ctx, char *opt);
int 	  ft_tr_error_arg(t_trace *ctx, char *opt, char *arg);
int 	  ft_tr_error_arg_handle(t_trace *ctx, char *opt, char *arg);

#endif
