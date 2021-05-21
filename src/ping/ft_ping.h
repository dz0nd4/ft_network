/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 14:21:50 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <signal.h>

# include "../ft_network_global.h"
# include "../traceroute/ft_traceroute.h"

# define FT_IPHDR_LEN                 20
# define FT_ICMPHDR_LEN               8

# define FT_PING_ICMPHDR              FT_IPHDR_LEN + FT_ICMPHDR_LEN

# define PACKETSIZE	64
# define FT_PING_PACKETSIZE_DEFAULT	  56
# define FT_PING_PACKETSIZE_MAX	      65507
# define FT_PING_DEFAULT_TTL      	  64
# define FT_PING_DEFAULT_DELAY      	1
# define FT_PING_DEFAULT_DELAY      	1


/*
 *  Globals
*/
extern int g_ping_run;
extern int g_ping_send;

typedef unsigned char     t_uchar;
typedef struct s_pg       t_pg;
extern t_pg g_pg;

typedef struct s_ping_args  t_pg_args;
typedef struct s_ping_opts  t_pg_opts;
typedef struct s_ping       t_ping;
typedef int                 t_ping_opt_ft(t_pg_opts *opts, t_pg_args *args);

extern t_ping   g_ctx;

/*
 *  Args
*/
typedef struct			s_ping_args
{
	int           	argc;
	const char		  **argv;
	int         	  argi;
}						t_pg_args;


typedef struct  s_sock_icmp_type
{
  int   type_int;
  char  *type_str;
}               t_sock_icmp_type;

/*
 *  Options
*/
typedef enum			e_ping_opt_key
{
	FT_PING_OPT_H,
	FT_PING_OPT_V,
  FT_PING_OPT_N,
	FT_PING_OPT_S,
	FT_PING_OPT_T,
	FT_PING_OPT_MAX
}						t_ping_opt_key;

typedef struct			s_ping_opt_dispatch
{
	t_ping_opt_key	opt_key;
	char				    *opt_name;
	t_ping_opt_ft	  *opt_dist;
}						t_ping_opt_d;

typedef struct    s_ping_opts
{
  int   argi;
  char  *host;
  int   verbose;
  int   flood;
  int   numeric_only;
  int   ttl;
  int   packetsize;
}                 t_pg_opts;

/*
 *  Socket
*/

// typedef struct s_pg_pckt
// {
// 	t_icmphdr   hdr;
//   char        msg[PACKETSIZE - sizeof(t_icmphdr)];
// }             t_pg_pckt;

typedef struct s_pg_pckt
{
	t_icmphdr   hdr;
  char        *msg;
}             t_pg_pckt;

typedef struct s_pg_pckt_recv
{
  t_ip        ip;
	t_icmphdr   hdr;
  char        *msg;
  char        addr[128];
  int         cc;
}             t_pg_pckt_recv;

typedef struct s_pg_sock
{
  int         id;
  int         fd;
  const char  *host;
  t_sockaddr_in addrin;
  t_uchar     *send_pckt;
  int         send_pckt_len;
  t_uchar     *recv_pckt;
  int         recv_pckt_len;
}              t_pg_sock;

/*
 *  Statistics
*/
typedef struct  s_ping_stats
{
  t_tr_time time;
  int nbPcktSend;
  int nbPcktReceive;
  int nbPcktLoss;
  double minTime;
  double avgTime;
  double maxTime;
}               t_pg_stats;

typedef struct  s_ping_msg
{
  t_msghdr msg;
  t_iovec iov;
  char packet[400];
  char addrbuf[128];
  int cc;
}               t_pg_msg;

typedef struct		s_ping
{
  int           sfd;
  const char    *host;
  t_pg_opts    opts;
  char          send_buf[400];
  char          *packet;
  int           count;
  t_pg_pckt      pckt;
  t_tr_time     time;
  t_pg_stats  stats;
}					t_ping;

typedef struct s_pg
{
  t_pg_sock   sock;
  t_pg_opts   opts;
  t_pg_stats  stats;
}         t_pg;

/*
 *  FUNCTIONS PROTOYPES
*/

int			ft_ping(int argc, const char *argv[]);

/*
 *  Options
*/
int 	  ft_ping_opts_init(t_pg_opts	*opts);
int		ft_ping_opts_parse(t_pg_opts *opts, t_pg_args *args);
// int		  ft_ping_opts_parse(t_pg_opts *opts, const char *opt, const char *arg);

int     ft_ping_opt_h(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_v(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_n(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_s(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_t(t_pg_opts *opts, t_pg_args *args);

/*
 *  Execute
*/
int     ft_ping_exec(const char *dst, t_pg_opts opts);
int		  ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats);
int		  ft_ping_exec_receive(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats);
int     ft_ping_exec_stats(t_pg_stats stats);

void 	  ft_ping_exec_sigint(int signo);
void 	  ft_ping_exec_sigarlm(int signo);

int		  ft_ping_exec_print_infos(const char *dst, t_pg_sock	sock, t_pg_opts opts);
int     ft_ping_exec_print_stats(const char *dst, t_pg_stats stats);
int     ft_ping_exec_print_pckt(int cc, char *addr, int seq, int ttl, double time);
double  ft_ping_execute_recv_print_time(t_tr_time *time);
int     ft_ping_exec_print_stats2(t_pg_stats stats);
int     ft_pg_exec_print_pckt(char *addr, int seq, int icmp_type);

/*
 *  Erros
*/
int     ft_ping_exit(char *s);
int     ft_ping_usage();
int     ft_ping_error_host(const char *dest);


int 	  ft_ping_error_opt_ttl();
int     ft_ping_err_exec_recv(const char *err);

/*
 *  Socket
*/
int     ft_sock_recvmsg(int sfd, char *addr, char *packet, int packetlen);

int		  ft_sock_ntop(t_in_addr *src, char *dst);

unsigned short ft_sock_cksum(void *b, int len);
int		  ft_sock_gettime(t_timeval *tv);
int		  ft_sock_delay();
double   ft_sock_timediff(t_timeval *out, t_timeval *in);
int    ft_socket_getnameinfo(t_sockaddr_in *host, char *name);
double     ft_sock_getelapsedtime(t_timeval *in);
char *ft_sock_get_icmp_type(int type);

void hexdump(void *mem, unsigned int len);

#endif
