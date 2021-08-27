/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/27 14:46:57 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include "../ft_network_global.h"

#define DEFAULT_DATA_SIZE 32       // default data size
#define DEFAULT_RECV_TIMEOUT 6000  // six second
#define DEFAULT_TTL 30             // default timeout
#define BUF_SIZE 1024

#define FT_ADDRSTRLEN 16
#define FT_PORT_DEFAULT 33435

#define FT_TR_ROOT 0

#define FT_HOPS_FIRST_DEFAULT 1
#define FT_HOPS_MAX_DEFAULT 30
#define FT_HOPS_MAX 255

#define FT_PROBES_DEFAULT 3
#define FT_PROBES_MAX 10

#define FT_PORT_DEFAULT 33435

#define FT_PACKETLEN_DEFAULT sizeof(struct ip) + 40

#define FT_PACKETLEN_MAX 65000

// # define FT_NI_MAXHOST          1025
#define FT_NI_MAXSERV 32


// struct opacket {
// 	struct ip ip;
// 	struct udphdr udp;
// 	u_char seq;		/* sequence number of this packet */
// 	u_char ttl;		/* ttl packet left with */
// 	struct timeval tv;	/* time packet left */
// };

// typedef struct s_traceroute t_trace;

/*
 *  Options
 */
typedef enum e_trace_opt_key {
  FT_TR_OPT_F,
  FT_TR_OPT_M,
  FT_TR_OPT_Q,
  FT_TR_OPT_H,
  FT_TR_OPT_MAX
} t_tr_opt_key;

typedef struct s_trace_options {
  int argi;
  const char *host;
  int packetlen;
  int hops;
  int hops_max;
  int probes;
  int probes_max;
  int port;
} t_tr_opts;

typedef int t_tr_ft_opt(t_tr_opts *opts, t_arg *arg);

typedef struct s_trace_option_dispatch {
  t_tr_opt_key opt_key;
  char *opt_name;
  t_tr_ft_opt *opt_dist;
} t_tr_opt_d;

/*
 *  Execute
 */
typedef struct s_tr_time {
  t_timeval start;
  t_timeval stop;
} t_tr_time;

typedef struct s_trace_sock {
  int fd;
  t_sockaddr_in saddrin;
  int cc;
  char *data;
  int datalen;
  t_timeval tv;
} t_tr_sock;

// typedef struct s_traceroute {
//   t_tr_opts opts;
//   t_tr_time time;
//   t_tr_sock sto;
//   t_tr_sock sfrom;
// } t_trace;

typedef struct s_trace {
  const char *host;
  int packetlen;
  int hops;
  int hops_max;
  int probes;
  int probes_max;
  int port;
} t_trace;

int ft_traceroute(int argc, const char *argv[]);
int ft_traceroute_usage();

/*
 *  Parse
 */
int ft_trace_parse(t_tr_opts *opts, int argc, const char *argv[]);

int ft_tr_opt_f(t_tr_opts *opts, t_arg *arg);
int ft_tr_opt_m(t_tr_opts *opts, t_arg *arg);
int ft_tr_opt_q(t_tr_opts *opts, t_arg *arg);
int ft_tr_opt_h(t_tr_opts *opts, t_arg *arg);

int ft_tr_arg_host(t_tr_opts *opts, t_arg *arg);
int ft_tr_arg_packetlen(t_tr_opts *opts, t_arg *arg);

int ft_tr_err_opt_require_arg(t_arg *arg, const char *desc);
int ft_tr_err_opt_handle(t_arg *arg);
int ft_tr_err_arg_host(t_arg *arg);
int ft_tr_err_arg_packetlen(t_arg *arg);

/*
 *  Execute
 */
int ft_trace_execute(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from);

int ft_trace_exec_init_to(t_tr_opts *opts, t_tr_sock *to);
int ft_trace_exec_init_from(t_tr_opts *opts, t_tr_sock *from);

int ft_trace_exec_send(t_tr_opts *opts, t_tr_sock *to);
int ft_trace_exec_recv(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from);
int ft_trace_exec_pckt(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from);

int ft_trace_exec_finish_to(t_tr_sock *to);
int ft_trace_exec_finish_from(t_tr_opts *opts, t_tr_sock *from);

#endif
