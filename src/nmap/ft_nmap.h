/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:10:56 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 18:06:27 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
#define FT_NMAP_H

#include <poll.h>

#include "../ft_network_global.h"

#define FT_NMAP_BUFFER_DEFAULT 256

#define FT_NMAP_PORTS_MAX 1024
#define FT_NMAP_IP_MAX 1024

#define FT_NMAP_TCP 0
#define FT_NMAP_UDP 1

#define DEFAULT "\033[0m"
#define HIGHLIGHT "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define FT_NMAP_THREADS_MAX 250

pthread_mutex_t g_mutex;

typedef pthread_mutex_t t_mutex;
typedef pthread_t t_pthread;

/*
 *  Port state
 */

typedef enum e_nmap_port_state {
  FT_NMAP_CLOSE,
  FT_NMAP_UNFILTERED,
  FT_NMAP_OPEN_FILTERED,
  FT_NMAP_FILTERED,
  FT_NMAP_OPEN,
  FT_NMAP_PORT_STATE,
} t_nmap_port_state;

/*
 *  Scan types
 */

typedef enum e_nmap_scan_types {
  FT_NMAP_SCAN_SYN = 1 << 0,
  FT_NMAP_SCAN_NULL = 1 << 1,
  FT_NMAP_SCAN_ACK = 1 << 2,
  FT_NMAP_SCAN_FIN = 1 << 3,
  FT_NMAP_SCAN_XMAS = 1 << 4,
  FT_NMAP_SCAN_UDP = 1 << 5,
  FT_NMAP_SCAN_MAX = 6
} t_nmap_scan_types;

typedef int t_nmap_resps_ft(t_tcphdr *tcp, int timeout);

typedef struct s_nmap_res_scan_dispatch {
  t_nmap_scan_types scan_key;
  t_nmap_resps_ft *scan_dist;
} t_nmap_resps_d;

/*
 *  Result
 */

typedef struct s_nmap_result_port_scan {
  int key;
  int port;
  int proto;
  int state;
  char *addr;
  char *dev;
  char *ip;
  t_sockaddr_in in;
  // const char *key_str;
  // const char *state_str;
} t_nmap_resps;

typedef struct s_nmap_res {
  int port;
  int service;
  t_nmap_resps res_scan[FT_NMAP_SCAN_MAX];
  int conclusion;
} t_nmap_res;

typedef struct s_nmap_result_port {
  int port;
  int scan;
  t_nmap_resps res_scan[FT_NMAP_SCAN_MAX];
  int conclusion;
} t_nmap_resp;

/*
 *  Options
 */

typedef enum e_nmap_opt_key {
  FT_NMAP_OPT_HELP,
  FT_NMAP_OPT_PORTS,
  FT_NMAP_OPT_IP,
  FT_NMAP_OPT_FILE,
  FT_NMAP_OPT_SPEEDUP,
  FT_NMAP_OPT_SCAN,
  FT_NMAP_OPT_MAX
} t_nmap_opt_key;

typedef struct s_nmap_opts {
  char ip[FT_NMAP_IP_MAX][256];
  int nip;
  char *file;
  int nports;
  int ports[FT_NMAP_PORTS_MAX];
  int p[FT_NMAP_PORTS_MAX][2];
  int speedup;
  int scan;
} t_nmap_opts;

typedef int t_nmap_opt_ft(t_nmap_opts *opts, t_arg *arg);

typedef struct s_nmap_opts_dispatch {
  t_nmap_opt_key opt_key;
  char *opt_name;
  t_nmap_opt_ft *opt_dist;
} t_nmap_opts_d;

/*
 *  Context
 */

typedef struct s_nmap_device {
  char *name;     /* The device name to sniff on */
  char *addr;     /* The device addr to sniff on */
  t_bpf net;      /* Our IP */
  t_bpf mask;     /* Our netmask */
  pcap_t *handle; /* The session handler */
} t_nmap_dev;

// typedef struct s_nmap_dev {
//   char *name;                /* The device name to sniff on */
//   char *addr;                /* The device addr to sniff on */
//   struct bpf_program fp;     /* The compiled filter */
//   char *filter_exp;          /* The filter expression */
//   bpf_u_int32 net;           /* Our IP */
//   bpf_u_int32 mask;          /* Our netmask */
//   struct pcap_pkthdr header; /* The header that pcap gives us */
//   const t_uchar *packet;     /* The actual packet */
// } t_nmap_dev;

typedef struct s_nmap_thread {
  pthread_t fd;
  int lock;
} t_nmap_thr;

typedef struct s_nmap_multi_thread {
  t_nmap_thr thr[FT_NMAP_THREADS_MAX];
  int ithr;
} t_nmap_mthr;

typedef struct s_nmap_context {
  char *sdev;
  char *saddr;
  char ip[256];
  int iport;
  pthread_t threads[FT_NMAP_THREADS_MAX];
  int ithreads;
  int iscan;

  t_nmap_res res[FT_NMAP_PORTS_MAX];
  t_nmap_resp resp[FT_NMAP_PORTS_MAX];
  t_nmap_resp resp_open[FT_NMAP_PORTS_MAX];
  t_nmap_resp resp_close[FT_NMAP_PORTS_MAX];

  int ires_open;
  t_nmap_res res_open[FT_NMAP_PORTS_MAX];
  int ires_close;
  t_nmap_res res_close[FT_NMAP_PORTS_MAX];
} t_nmap_ctx;

typedef struct s_nmap {
  char *dev;        /* The device name to sniff on */
  char *addr;       /* The device addr to sniff on */
  t_nmap_ctx ctx;   /* The context of ip scanned */
  t_nmap_opts opts; /* The options for scans */
} t_nmap;

int ft_nmap(int argc, const char *argv[]);
int ft_nmap_usage();

/*
 *  Options
 */
int ft_nmap_parse(t_nmap_opts *opts, int argc, const char *argv[]);

int ft_nmap_opt_ports(t_nmap_opts *opts, t_arg *arg);
int ft_nmap_opt_ip(t_nmap_opts *opts, t_arg *arg);
int ft_nmap_opt_file(t_nmap_opts *opts, t_arg *arg);
int ft_nmap_opt_speedup(t_nmap_opts *opts, t_arg *arg);
int ft_nmap_opt_scan(t_nmap_opts *opts, t_arg *arg);
int ft_nmap_opt_help(t_nmap_opts *opts, t_arg *arg);

/*
 *  Execute
 */
void ft_nmap_init_config(t_nmap_ctx *ctx);
int ft_nmap_exec_config(t_nmap_ctx ctx, t_nmap_opts opts);
int ft_nmap_exec_port_scan();

int ft_nmap_exec(t_nmap_ctx ctx, t_nmap_opts opts);
int ft_nmap_exec_port(t_nmap_ctx *ctx, t_nmap_opts opts, t_sockaddr_in in);

int ft_nmap_exec_send(t_nmap_ctx ctx, t_nmap_opts opts, t_sockaddr_in in,
                      int scan);
// void ft_nmap_execute_recv(t_uchar *user, const t_pcap_pkthdr *pkthdr,
//                           const t_uchar *pkt);

int ft_nmap_exec_recv(t_nmap_ctx *ctx, t_nmap_opts opts, int scan, int iscan,
                      pcap_t *handle);
void ft_nmap_exec_recv_handle(t_uchar *user, const t_pcap_pkthdr *pkthdr,
                              const t_uchar *pkt);
int ft_nmap_result(t_nmap_ctx ctx, t_nmap_opts opts);

/*
 *  Results
 */
void ft_nmap_res_header(int state);

// int ft_nmap_exec(t_nmap_opts *opts);
// int ft_nmap_exec_send(t_nmap *ctx);
// int ft_nmap_exec_recv(t_nmap *ctx, int port, int scan);

#endif
