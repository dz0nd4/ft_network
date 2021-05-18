/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 23:01:38 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <signal.h>

# include "../ft_network_global.h"
# include "../traceroute/ft_traceroute.h"


# define PACKETSIZE	64
# define FT_PING_DEFAULT_PACKETSIZE	  64
# define FT_PING_DEFAULT_TTL      	  64
# define FT_PING_DEFAULT_DELAY      	1


/*
 *  Globals
*/
extern int g_ping_run;
extern int g_ping_send;


typedef struct s_ping_opts  t_pg_opts;
typedef struct s_ping       t_ping;
typedef int                 t_ping_opt_ft(t_pg_opts *opts, const char *arg);

extern t_ping   g_ctx;

/*
 *  Options
*/
typedef enum			e_ping_opt_key
{
	FT_PING_OPT_H,
	FT_PING_OPT_V,
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
typedef struct s_pg_sock
{
  int         id;
  int         fd;
  t_addrinfo  addrinfo;
}              t_pg_sock;

/*
 *  Packet
*/
typedef struct s_ping_packet
{
	t_icmp      icmp;
  char        msg[PACKETSIZE - sizeof(t_icmphdr)];
}             t_pg_pckt;

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


/*
 *  FUNCTIONS PROTOYPES
*/

int			ft_ping(int argc, const char *argv[]);

/*
 *  Options
*/
int 	  ft_ping_opts_init(t_pg_opts	*opts);
int		  ft_ping_opts_parse(t_pg_opts *opts, const char *opt, const char *arg);

int     ft_ping_opt_h(t_pg_opts *opts, const char *arg);
int     ft_ping_opt_v(t_pg_opts *opts, const char *arg);

/*
 *  Execute
*/
int     ft_ping_exec(const char *dst, t_pg_opts opts);
int		  ft_ping_exec_send(t_pg_sock sock, t_pg_opts opts, t_pg_stats *stats);
int		  ft_ping_exec_receive(t_pg_sock sock, t_pg_stats *stats);

void 	  ft_ping_exec_sigint(int signo);
void 	  ft_ping_exec_sigarlm(int signo);

int		  ft_ping_exec_print_infos(const char *dst, t_pg_sock	sock);
int     ft_ping_exec_print_stats(const char *dst, t_pg_stats stats);
void    ft_ping_exec_print_pckt(int cc, char *addrbuf, char *packet, double time);
double   ft_ping_execute_recv_print_time(t_tr_time *time);

/*
 *  Erros
*/
int     ft_ping_exit(char *s);
int     ft_ping_usage();
int     ft_ping_error_host(const char *dest);

/*
 *  Socket
*/

int		ft_sock_ntop(t_in_addr *src, char *dst);

unsigned short ft_sock_cksum(void *b, int len);
int		  ft_sock_gettime(t_timeval *tv);
int     ft_sock_recvmsg(int sfd, char *addr, char *packet, int packetlen);
int		  ft_ping_delay();

#endif
