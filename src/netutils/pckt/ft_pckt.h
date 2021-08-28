/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pckt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:07:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PCKT_H
#define FT_PCKT_H

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

#include "../../ft_net_global.h"

/*
 *  IP
 */
#define FT_IPHDR_LEN sizeof(struct iphdr)

#define FT_IPIHL 5             /* Header length */
#define FT_IPVERSION IPVERSION /* IP version number */
#define FT_IP_MAXPCKT IP_MAXPACKET

typedef struct iphdr t_iphdr;

/*
 *  ICMP
 */
#define FT_ICMPHDR_LEN sizeof(struct icmphdr)

#define FT_NR_ICMP_TYPES NR_ICMP_TYPES + 1
#define FT_NR_ICMP_UNREACH NR_ICMP_UNREACH + 1
#define FT_NR_ICMP_REDIR ICMP_REDIR_HOSTTOS + 1
#define FT_NR_ICMP_EXC ICMP_EXC_FRAGTIME + 1

typedef struct icmphdr t_icmphdr;

typedef struct s_sock_icmp_type {
  int type_int;
  char *type_str;
} t_sock_icmp_type;

/*
 *  PCKT
 */
typedef struct s_pckt_ip {
  t_uint32 ihl;
  t_uint32 ver;
  t_uint32 daddr;
  t_uint16 len;
  t_uint16 id;
  t_uint8 proto;
  t_uint8 ttl;
} t_pckt_ip;

typedef struct s_pckt_icmp {
  t_uint16 id;
  t_uint16 seq;
  t_uint8 type;
} t_pckt_icmp;

typedef struct s_pckt_opt {
  t_pckt_ip ip;
  union {
    t_pckt_icmp icmp;
  };
} t_pckt_opt;

typedef struct s_pckt {
  int fd;
  int cc;
  t_uint16 id;
  t_uint16 len;
  struct sockaddr_in to;
  t_uchar *data;
} t_pckt;

/*
 *  PCKT IP
 */

void ft_pckt_ip_opt_default(t_pckt_ip *opts);
void ft_pckt_ip_opt_set(t_pckt *pckt, t_pckt_ip *opts);

/*
 *  PCKT ICMP
 */
void ft_pckt_icmp_opt_default(t_pckt_icmp *opt);
void ft_pckt_icmp_opt_set(t_pckt *pckt, t_pckt_icmp *opts);

char *ft_pckt_icmp_type(int type);
char *ft_pckt_icmp_code_unreach(int code);
char *ft_pckt_icmp_code_redir(int code);
char *ft_pckt_icmp_code_exc(int code);

/*
 *  PCKT TOOLS
 */
unsigned short ft_checksum(void *b, int len);
t_uchar *ft_pckt_random_data(t_uchar *data, t_uint16 len);
void ft_pckt_set_time(t_uchar *data);

#endif
