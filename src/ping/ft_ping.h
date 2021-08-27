/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/30 14:08:48 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <signal.h>

#include "../ft_network_global.h"

#define FT_PING_PACKETSIZE_DEFAULT 56
#define FT_PING_PACKETSIZE_MAX 65507

#define FT_PING_TTL_DEFAULT 64
#define FT_PING_TTL_MAX 255

#define FT_PING_DEFAULT_DELAY 1
#define FT_PING_DEFAULT_RECVTIMEOUT 1

#define FT_PING_STOP 0
#define FT_PING_RUN 1
#define FT_PING_SEND 2

// typedef struct s_ping_args t_arg;
typedef struct s_ping_opts t_pg_opts;
typedef int t_ping_opt_ft(t_pg_opts *opts, t_arg *args);

/*
 *  Globals
 */
extern int g_ping;

/*
 *  Args
 */
// typedef struct s_ping_args {
//   int argc;
//   const char **argv;
//   int argi;
// } t_arg;

/*
 *  Options
 */
typedef enum e_ping_opt_key {
  FT_PING_OPT_H,
  FT_PING_OPT_V,
  FT_PING_OPT_N,
  FT_PING_OPT_S,
  FT_PING_OPT_T,
  FT_PING_OPT_MAX
} t_ping_opt_key;

typedef struct s_ping_opt_dispatch {
  t_ping_opt_key opt_key;
  char *opt_name;
  t_ping_opt_ft *opt_dist;
} t_ping_opt_d;

typedef struct s_ping_opts {
  const char *dest;
  int verbose;
  int flood;
  int numeric_only;
  int ttl;
  int packetsize;
  t_pckt_opt opt;
} t_pg_opts;

/*
 *  Statistics
 */
typedef struct s_ping_stats {
  t_timeval start;
  int nbPcktSend;
  int nbPcktReceive;
  int nbPcktLoss;
  double minTime;
  double avgTime;
  double maxTime;
  double sumTime;
  double sum2Time;
} t_pg_stats;

typedef struct s_ping {
  int fd;
  int id;
  t_sockaddr_in to;
  t_pg_opts pg_opts;
  t_pg_stats stats;
} t_ping;

/*
 *  FUNCTIONS PROTOYPES
 */

int ft_ping(int argc, const char *argv[]);
int ft_ping_usage();
void ft_ping_sigint();
void ft_ping_sigarlm();

/*
 *  Options
 */
int ft_ping_parse(t_pg_opts *opts, int argc, const char *argv[]);

int ft_ping_opt_h(t_pg_opts *opts, t_arg *args);
int ft_ping_opt_v(t_pg_opts *opts, t_arg *args);
int ft_ping_opt_n(t_pg_opts *opts, t_arg *args);
int ft_ping_opt_s(t_pg_opts *opts, t_arg *args);
int ft_ping_opt_t(t_pg_opts *opts, t_arg *args);

/*
 *  Execute
 */
int ft_ping_execute(t_pg_opts opts);

// int ft_ping_exec_init(t_pg_opts opts, t_pg_sock *sock, t_pg_stats *stats);
int ft_ping_exec_finish(t_ping *ctx);
int ft_ping_exec_send(t_ping *ctx);
int ft_ping_exec_recv(t_ping *ctx);

/*
 *  Print
 */
// int ft_ping_exec_print_dest(t_pg_opts opts, t_pg_sock *sock);
int ft_ping_exec_print_addr(t_sockaddr_in *addrin, int numeric_only);

#endif
