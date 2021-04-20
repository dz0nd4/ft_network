/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/20 16:40:42 by user42           ###   ########lyon.fr   */
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

# include <netinet/ip.h>
# include <netinet/udp.h>

# include "../ft_network_global.h"

#define DEFAULT_DATA_SIZE      32       // default data size
#define DEFAULT_RECV_TIMEOUT   6000     // six second
#define DEFAULT_TTL            30       // default timeout
#define BUF_SIZE 1024

# define FT_ADDRSTRLEN 16
# define FT_PORT_DEFAULT  33435

# define FT_TR_ROOT             0


# define FT_DEFAULT_HOPS         1
# define FT_DEFAULT_HOPS_MAX     30
# define FT_DEFAULT_PROBES_MAX   3
# define FT_DEFAULT_PORT         33435
# define FT_DEFAULT_PACKET_LEN sizeof(struct ip) + 40

# define FT_PACKET_LEN_MAX      65000

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
typedef struct ip t_ip;
typedef struct udphdr t_udp;
typedef struct icmp t_icmp;

typedef struct timeval t_timeval;

struct opacket {
	struct ip ip;
	struct udphdr udp;
	u_char seq;		/* sequence number of this packet */
	u_char ttl;		/* ttl packet left with */
	struct timeval tv;	/* time packet left */
};

typedef struct  s_tr_packet {
  t_ip  ip;
  t_udp udp;
}       t_tr_pack;

typedef struct    s_tr_time
{
  t_timeval start;
  t_timeval stop;
}                 t_tr_time;

typedef struct    s_tr_sock
{
  int   udp;
  int   icmp;
  t_tr_pack udp_pack;
}                 t_tr_sock;

typedef struct    s_tr_host
{
  char  *name;
  char  ip[FT_ADDRSTRLEN];
  char  ip_last[FT_ADDRSTRLEN];
  t_sockaddr_in from;
  t_sockaddr_in to;
}                 t_tr_host;

typedef struct    s_tr_options
{
  int   hops;
  int   hops_max;
  int   probes;
  int   probes_max;
  int   port;
  int   packetlen;
}                 t_tr_opt;

typedef struct		s_traceroute
{
  int         argi;
  t_tr_sock   sock;
  t_tr_time   time;
  t_tr_host   host;
  t_tr_opt    opts;
  t_sockaddr_in from;
  t_sockaddr_in to;
  t_timeval   tv;
}					t_trace;

typedef int   t_tr_ft_arg(t_trace *ctx, char *arg);

/*
 *  Arguments
*/

typedef enum			e_tr_opt_key
{
	FT_TR_OPT_F,
	FT_TR_OPT_M,
	FT_TR_OPT_Q,  
	FT_TR_OPT_W,
	FT_TR_OPT_MAX
}						t_tr_opt_key;

typedef struct			s_tr_opt_dispatch
{
	t_tr_opt_key		opt_key;
	char				    *opt_name;
	t_tr_ft_arg	    *opt_dist;
}						t_tr_opt_d;

int			ft_traceroute(int argc, const char *argv[]);

// int			ft_traceroute_init(t_trace *ctx, int argc, const char *argv[]);
// int	    ft_tr_init_args(t_trace *ctx);
int 	  ft_tr_init_target(t_trace *ctx);
int 	  ft_tr_init_target_debug(t_trace *ctx);
int	ft_tr_init_sockets(t_trace *ctx);
int		ft_tr_init_opts(t_trace *ctx);

// int			ft_traceroute_args(t_trace *ctx, int argc, const char *argv[]);
// int 		ft_traceroute_exec(t_trace *ctx);

// int     ft_traceroute_send(t_trace *ctx);
// int     ft_traceroute_receive(t_trace *ctx, int ttl);
// int     ft_traceroute_receive(t_trace *ctx);
int 	  ft_tr_init_local(t_trace *ctx);
/*
 *  Errors
*/

/*
 *  Display
*/

int			ft_traceroute_usage(char *prgm);
int     ft_traceroute_print(t_trace *ctx, int cc);

/*
 *  Parser
*/

int			ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[]);
int			ft_traceroute_parse_debug(t_trace *ctx);

int			ft_tr_opt_f(t_trace *ctx, char *arg);
int			ft_tr_opt_m(t_trace *ctx, char *arg);
int			ft_tr_opt_q(t_trace *ctx, char *arg);
int			ft_tr_opt_w(t_trace *ctx, char *arg);
int			ft_tr_opt_h(t_trace *ctx, char *arg);

int			ft_tr_arg_packetlen(t_trace *ctx, char *arg);

/*
 *  Exec
*/

int 		ft_traceroute_exec(t_trace *ctx);
int     ft_traceroute_exec_send(t_trace *ctx);
int     ft_traceroute_exec_receive(t_trace *ctx);

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
int 	  ft_tr_error_host();

#endif
