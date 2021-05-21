/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:44:55 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

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

// # define FT_NI_MAXHOST          1025
# define FT_NI_MAXSERV          32

// struct opacket {
// 	struct ip ip;
// 	struct udphdr udp;
// 	u_char seq;		/* sequence number of this packet */
// 	u_char ttl;		/* ttl packet left with */
// 	struct timeval tv;	/* time packet left */
// };

typedef struct  s_tr_pack_hdr_udp {
  t_ip  ip;
  t_udp udp;
}       t_tr_pack_hdr_udp;

typedef struct  s_tr_pack_hdr_icmp {
  t_ip  ip;
  t_icmp icmp;
}       t_tr_pack_hdr_icmp;

typedef struct  s_tr_packet_hdr {
  t_ip  ip;
  t_udp udp;
}       t_tr_pack_hdr;

typedef struct  s_tr_opacket {
  t_tr_pack_hdr hdr;
  char  *data;
  int   datalen;
}       t_tr_opacket;

typedef struct  s_tr_packet {
  t_ip  ip;
  t_udp udp;
  char  *data;
  int   datalen;
}       t_tr_pack;

typedef struct    s_tr_time
{
  t_timeval start;
  t_timeval stop;
}                 t_tr_time;

typedef struct    s_tr_sock
{
  t_tr_pack udp_pack;
  char  *data;
  int   datalen;
}                 t_tr_sock;

typedef struct    s_tr_from
{
  int             sfd;
  t_sockaddr_in   saddrin;
  int             saddrin_size;
  t_timeval       wait;
  char            buffer[BUF_SIZE];
  int             cc;
  int             code;
  char            ip_last[FT_ADDRSTRLEN];
}                 t_tr_from;

typedef struct    s_tr_to
{
  int             sfd;
  t_addrinfo      addrinfo;
  t_sockaddr_in   saddrin;
  char            *name;
  char            ip[FT_ADDRSTRLEN];
  t_tr_pack       pack;
  t_tr_pack_hdr   *hdr;
}                 t_tr_to;

typedef struct    s_tr_options
{
  int   argi;
  int   hops;
  int   hops_max;
  int   probes;
  int   probes_max;
  int   port;
  int   packetlen;
}                 t_tr_opt;

typedef struct		s_traceroute
{
  t_tr_opt    opts;
  t_tr_to     to;
  t_tr_from   from;
  t_tr_time   time;
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
int			ft_traceroute_parse(t_trace *ctx, int argc, const char *argv[]);
int 		ft_traceroute_execute(t_trace *ctx);


int     ft_tr_resolve(t_sockaddr_in *from, char *name);

/*
 *  Parse
*/

int			ft_tr_opt_f(t_trace *ctx, char *arg);
int			ft_tr_opt_m(t_trace *ctx, char *arg);
int			ft_tr_opt_q(t_trace *ctx, char *arg);
int			ft_tr_opt_w(t_trace *ctx, char *arg);
int			ft_tr_opt_h(t_trace *ctx, char *arg);

int			ft_tr_arg_host(t_trace *ctx, char *arg);
int			ft_tr_arg_packetlen(t_trace *ctx, char *arg);

/*
 *  Execute
*/
int   ft_traceroute_execute_send_init(t_tr_to *to);
int   ft_traceroute_execute_pack_init(t_trace *ctx, t_tr_to *to);
int   ft_traceroute_execute_recv_init(t_tr_from *from);
int   ft_traceroute_execute_send(t_trace *ctx, t_tr_opt *opts, t_tr_to *to);
int   ft_traceroute_execute_recv(t_trace *ctx, char *buffer, t_tr_from *from);

/*
 *  Socket
*/

// int     ft_sock_getaddrinfo(const char *host, t_addrinfo *result);
// int     ft_sock_send(int fd, char *data, int datalen, t_sockaddr_in *saddrin);
// int     ft_sock_recv(int fd, char *data, int datalen, t_sockaddr_in *saddrin);
// int			ft_sock_pton(struct in_addr *addr, char *ipv4);

/*
 *  Errors
*/

void 	  ft_exit(char *s);
void    ft_traceroute_exit(char *s);

int 	  ft_trace_error_opt_bad(t_trace *ctx, char *opt);
int 	  ft_trace_error_opt_arg_require(t_trace *ctx, char *opt, char *arg);
int 	  ft_trace_error_opt_arg_handle(t_trace *ctx, char *opt, char *arg);

int 	  ft_tr_error_host();
int 	  ft_tr_error_host_resolve(t_trace *ctx, char *arg);
int 	  ft_tr_error_packetlen(t_trace *ctx, char *opt, char *arg);

#endif
