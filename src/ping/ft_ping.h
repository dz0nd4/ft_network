/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 16:06:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <signal.h>

#include "../ft_net_global.h"

/*
 *  Default values
 */
#define FT_PING_PACKETSIZE_DEFAULT 56
#define FT_PING_TTL_DEFAULT 64
#define FT_PING_DEFAULT_DELAY 1
#define FT_PING_DEFAULT_RECVTIMEOUT 1

/*
 *  Max values
 */
#define FT_PING_PACKETSIZE_MAX 65507
#define FT_PING_TTL_MAX 255

/*
 *  Globals
 */
#define FT_PING_HDR (FT_IPHDR_LEN + FT_ICMPHDR_LEN)
#define FT_PING_STOP 0
#define FT_PING_RUN 1
#define FT_PING_SEND 2

extern int g_ping;
typedef struct s_ping_opts t_ping_opts;
typedef int t_ping_opt_ft(t_ping_opts *opts, t_arg *args);

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
} t_ping_opts;

/*
 *  Results
 */
typedef struct s_ping_results {
  t_timeval start;
  int nbPcktSend;
  int nbPcktReceive;
  int nbPcktLoss;
  double minTime;
  double avgTime;
  double maxTime;
  double sumTime;
  double sum2Time;
} t_ping_res;

/*
 *  Context
 */
typedef struct s_ping_context {
  int id;
  int fd;
  t_sockaddr_in to;
} t_ping_ctx;

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
int ft_ping_parse(t_ping_opts *opts, int argc, const char *argv[]);

int ft_ping_opt_h(t_ping_opts *opts, t_arg *args);
int ft_ping_opt_v(t_ping_opts *opts, t_arg *args);
int ft_ping_opt_n(t_ping_opts *opts, t_arg *args);
int ft_ping_opt_s(t_ping_opts *opts, t_arg *args);
int ft_ping_opt_t(t_ping_opts *opts, t_arg *args);

/*
 *  Execute
 */
int ft_ping_exec(t_ping_res *stats, t_ping_opts opts);
int ft_ping_exec_send(t_ping_res *res, t_ping_opts opts, t_ping_ctx ctx);
int ft_ping_exec_recv(t_ping_res *res, t_ping_opts opts, t_ping_ctx ctx);

/*
 *  Result
 */
int ft_ping_res(t_ping_res res, t_ping_opts opts);

#endif
