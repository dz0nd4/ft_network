/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 23:47:34 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <signal.h>

# include "../ft_network_global.h"

# define FT_IPHDR_LEN                 20
# define FT_ICMPHDR_LEN               8
# define FT_TIMEVAL_LEN               16
# define FT_PING_ICMPHDR              FT_IPHDR_LEN + FT_ICMPHDR_LEN

# define FT_PING_PACKETSIZE_DEFAULT	  56
# define FT_PING_PACKETSIZE_MAX	      65507
# define FT_PING_DEFAULT_TTL      	  115
# define FT_PING_DEFAULT_DELAY      	1
# define FT_PING_DEFAULT_RECVTIMEOUT  1


# define FT_PG_STOP                   0
# define FT_PG_RUN                    1
# define FT_PG_SEND                   2

/*
 *  Globals
*/
extern int g_ping;
typedef unsigned char       t_uchar;

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

typedef struct s_pg_pckt
{
	t_icmphdr   hdr;
  int         msg_len;
}             t_pg_pckt;

typedef struct s_pg_pckt_recv
{
  int         cc;
  char        addr[128];
  char        *msg;
  int         msg_len;
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

typedef struct    s_pg_time
{
  t_timeval start;
  t_timeval stop;
}                 t_pg_time;

typedef struct  s_ping_stats
{
  t_pg_time time;
  int nbPcktSend;
  int nbPcktReceive;
  int nbPcktLoss;
  double minTime;
  double avgTime;
  double maxTime;
}               t_pg_stats;

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
int     ft_ping_usage();
void 	  ft_ping_sigint();
void 	  ft_ping_sigarlm();

/*
 *  Options
*/
int 	  ft_ping_opts_init(int argc, const char *argv[], t_pg_args *args, t_pg_opts	*opts);
int		  ft_ping_opts_parse(t_pg_opts *opts, t_pg_args *args);

int     ft_ping_opt_h(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_v(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_n(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_s(t_pg_opts *opts, t_pg_args *args);
int     ft_ping_opt_t(t_pg_opts *opts, t_pg_args *args);

/*
 *  Execute
*/
int     ft_ping_exec(const char *dst, t_pg_opts opts);
int     ft_ping_exec_init(const char *dst, t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats);
int     ft_ping_exec_finish(const char *dst, t_pg_sock *sock, t_pg_stats *stats);

int		  ft_ping_exec_send(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats);
int		  ft_ping_exec_receive(t_pg_sock *sock, t_pg_opts opts, t_pg_stats *stats);

void 	  ft_ping_exec_sigint(int signo);
void 	  ft_ping_exec_sigarlm(int signo);

#endif
