/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/27 17:53:45 by user42           ###   ########lyon.fr   */
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
  t_timeval       wait;
  char            buffer[BUF_SIZE];
  int             cc;
  int             code;
  char            ip_last[FT_ADDRSTRLEN];
}                 t_tr_from;

typedef struct    s_tr_to
{
  int             sfd;
  t_addrinfo      *addrinfo;
  t_sockaddr_in   saddrin;
  char            *name;
  char            ip[FT_ADDRSTRLEN];
  t_tr_pack       pack;
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

/*
 *  Display
*/

int     ft_traceroute_display_infos_host(t_trace *ctx);
int			ft_traceroute_usage(char *prgm);
int     ft_traceroute_print(t_trace *ctx, int cc);

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
 *  Socket
*/

int     ft_traceroute_packet_init(t_trace *ctx);
int     ft_traceroute_packet_set_header(t_trace *ctx);
int     ft_traceroute_packet_check(t_trace *ctx, char *buffer);

int     ft_traceroute_socket_send_init(t_trace *ctx);
int     ft_traceroute_socket_send(t_trace *ctx);

int     ft_traceroute_socket_receive_init(t_trace *ctx);
int     ft_traceroute_socket_receive(t_trace *ctx, char *buffer);

/*
 *  Errors
*/

void 	  ft_exit(char *s);
void    ft_traceroute_exit(char *s);

int 	  ft_tr_error_bad_opt(t_trace *ctx, char *opt);
int 	  ft_tr_error_arg(t_trace *ctx, char *opt, char *arg);
int 	  ft_tr_error_arg_handle(t_trace *ctx, char *opt, char *arg);

int 	  ft_tr_error_host();
int 	  ft_tr_error_host_resolve(t_trace *ctx, char *arg);
int 	  ft_tr_error_packetlen(t_trace *ctx, char *opt, char *arg);

#endif
