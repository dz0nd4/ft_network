/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/20 14:07:49 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SOCK_H
#define FT_SOCK_H

#include "../../libft/libft.h"

// # define FT_EXOK      0
// # define FT_EXFAIL    1
#define FT_NI_MAXHOST 1025
#define FT_ADDRSTRLEN 16

// #define __USE_MISC  // Enable network structures#
// #define __BSD_SOURCE

#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
// # include <errno.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>
#include <pcap/pcap.h>
#include <pthread.h>

/* TOLIB */

#define FT_UINT8_MAX 0xFF    /* 255 */
#define FT_UINT16_MAX 0xFFFF /* 65535 */

typedef struct s_arg {
  int i;
  int c;
  const char **v;
} t_arg;

typedef struct s_map_istr {
  int key;
  char *value;
} t_map_istr;

/*
  GLOBAL
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

typedef struct s_pckt_udp {
  t_uint16 len;
  t_uint16 sport;
  t_uint16 dport;
} t_pckt_udp;

typedef struct s_pckt_tcp {
  t_uint32 saddr;
  t_uint32 daddr;
  t_uint32 seq;
  t_uint32 ack_seq;
  t_uint16 sport;
  t_uint16 dport;
  t_uint16 doff;
  t_uint16 window;
  t_uint8 flags;
} t_pckt_tcp;

typedef struct s_pckt_opt {
  t_pckt_ip ip;
  union {
    t_pckt_icmp icmp;
    t_pckt_udp udp;
    t_pckt_tcp tcp;
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
 *  SOCKET
 */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int t_socket;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct in_addr t_in_addr;

#define FT_PING_HDR (FT_IPHDR_LEN + FT_ICMPHDR_LEN)
#define FT_TRACE_HDR (FT_IPHDR_LEN + FT_UDPHDR_LEN)

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

typedef struct icih_idseqih_idseqmp t_icmp;
typedef struct icmphdr t_icmphdr;

typedef struct s_sock_icmp_type {
  int type_int;
  char *type_str;
} t_sock_icmp_type;

/*
 *  UDP
 */
#define FT_UDPHDR_LEN sizeof(struct udphdr)

typedef struct udphdr t_udphdr;

/*
 *  TCP
 */
#define FT_TCPHDR_LEN sizeof(struct tcphdr)

#define FT_TCPDOFF 5 /* Header length */
typedef struct tcphdr t_tcphdr;

typedef struct pseudo_header  // needed for checksum calculation
{
  unsigned int source_address;
  unsigned int dest_address;
  unsigned char placeholder;
  unsigned char protocol;
  unsigned short tcp_length;

  t_tcphdr tcp;
} t_psh;

enum e_nmap_tcp_flag {
  FT_TCP_FLAG_URG = 1 << 0,
  FT_TCP_FLAG_ACK = 1 << 1,
  FT_TCP_FLAG_PSH = 1 << 2,
  FT_TCP_FLAG_RST = 1 << 3,
  FT_TCP_FLAG_SYN = 1 << 4,
  FT_TCP_FLAG_FIN = 1 << 5,
  FT_TCP_FLAG_MAX = 6
} t_nmap_tcp_flag;

// typedef struct addrinfo     t_addrinfo;

/*
 *  TIME
 */

#define FT_TIMEVAL_LEN sizeof(struct timeval)

typedef struct timeval t_timeval;

typedef struct msghdr t_msghdr;
typedef struct iovec t_iovec;

typedef struct ifaddrs t_ifaddrs;

/*
 *  PCAP
 */

typedef struct pcap_t t_pcap;
typedef struct pcap_pkthdr t_pcap_pkthdr;
typedef struct bpf_program t_bpf_program;
typedef bpf_u_int32 t_bpf;

/*
 *  ETHER
 */
#define FT_ETHHDR_LEN sizeof(struct ether_header)

typedef struct ether_header t_ethhdr;

/*
 *  INTEROPERABILITY
 */

#ifdef __APPLE__

#define FT_SOL_SOCKET SOL_SOCKET  // IPPROTO_IP
#define FT_NI_NAMEREQD 8          /* Don't return numeric addresses.  */
#define FT_AI_CANONNAME 0x0002    /* Request for canonical name.  */

typedef struct ip t_ip;

typedef struct s_icmphdr {
  u_int8_t type; /* message type */
  u_int8_t code; /* type sub-code */
  u_int16_t checksum;
  union {
    struct {
      u_int16_t id;
      u_int16_t sequence;
    } echo;            /* echo datagram */
    u_int32_t gateway; /* gateway address */
    struct {
      u_int16_t unused;
      u_int16_t mtu;
    } frag; /* path mtu discovery */
  } un;
} t_icmphdr;

typedef struct s_addrinfo {
  int ai_flags;               /* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
  int ai_family;              /* PF_xxx */
  int ai_socktype;            /* SOCK_xxx */
  int ai_protocol;            /* 0 or IPPROTO_xxx for IPv4 and IPv6 */
  socklen_t ai_addrlen;       /* length of ai_addr */
  char *ai_canonname;         /* canonical name for hostname */
  struct sockaddr *ai_addr;   /* binary address */
  struct s_addrinfo *ai_next; /* next structure in linked list */
} t_addrinfo;

// typedef struct s_addrinfo
// {
//   int ai_flags;			/* Input flags.  */
//   int ai_family;		/* Protocol family for socket.  */
//   int ai_socktype;		/* Socket type.  */
//   int ai_protocol;		/* Protocol for socket.  */
//   socklen_t ai_addrlen;		/* Length of socket address.  */
//   struct sockaddr *ai_addr;	/* Socket address for socket.  */
//   char *ai_canonname;		/* Canonical name for service location.
//   */ struct s_addrinfo *ai_next;	/* Pointer to next in list.  */
// }             t_addrinfo;

#endif

#ifdef __linux__

#define FT_SOL_SOCKET SOL_SOCKET
#define FT_AI_CANONNAME 0x0002 /* Request for canonical name.  */
#define FT_NI_NUMERICHOST 1    /* Don't try to look up hostname.  */
#define FT_NI_NUMERICSERV 2    /* Don't convert port number to name.  */
#define FT_NI_NOFQDN 4         /* Only return nodename portion.  */
#define FT_NI_NAMEREQD 8       /* Don't return numeric addresses.  */
#define FT_NI_DGRAM 16         /* Look up UDP service rather than TCP.  */
// typedef struct icmphdr t_icmphdr;

// typedef struct s_icmphdr {
//   uint8_t type; /* message type */
//   uint8_t code; /* type sub-code */
//   uint16_t checksum;
//   union {
//     struct {
//       uint16_t id;
//       uint16_t sequence;
//     } echo;           /* echo datagram */
//     uint32_t gateway; /* gateway address */
//     struct {
//       uint16_t __glibc_reserved;
//       uint16_t mtu;
//     } frag; /* path mtu discovery */
//   } un;
// } t_icmphdr;

// typedef struct addrinfo t_addrinfo;
typedef struct ip t_ip;

typedef struct s_addrinfo {
  int ai_flags;               /* Input flags.  */
  int ai_family;              /* Protocol family for socket.  */
  int ai_socktype;            /* Socket type.  */
  int ai_protocol;            /* Protocol for socket.  */
  socklen_t ai_addrlen;       /* Length of socket address.  */
  struct sockaddr *ai_addr;   /* Socket address for socket.  */
  char *ai_canonname;         /* Canonical name for service location.  */
  struct s_addrinfo *ai_next; /* Pointer to next in list.  */
} t_addrinfo;

#endif

/*
 *  SOCK RECV
 */
int ft_recvfrom(int fd, char *data, int datalen, t_sockaddr_in *saddrin);
int ft_recvmsg(int sfd, char *addr, char *packet, int packetlen);

/*
 *  SOCK SEND
 */
int ft_sendto(int fd, char *data, int datalen, t_sockaddr_in *saddrin);

/*
 *  SOCK TO
 */
int ft_inet_ntop(t_in_addr *src, char *dst);
int ft_inet_pton(struct in_addr *addr, char *ipv4);
int ft_inet_ntoa(t_in_addr *src, char *dst);

/*
 *  SOCK GET
 */
int ft_getaddrinfo(const char *host, t_addrinfo *result);
int ft_getnameinfo(t_sockaddr_in *host, char *name);
char *ft_getnameinfo_pr(t_sockaddr_in *host, char *hostname);
int ft_getifaddrs(t_ifaddrs **ifaddrs);
int ft_getifaddr(const char *dev_name, char **dev_addr);
int ft_getnameinfo_err(const char *bin, const char *hostname);
char *ft_getservbyport(int port, char *protocol);

/*
 *  SOCK TIME
 */
int ft_gettimeofday(t_timeval *tv);
int ft_delay();
double ft_timediff(t_timeval *out, t_timeval *in);
double ft_getelapsedtime(t_timeval *in);

int ft_setsockopt_ttl(int *fd, int ttl, int verbose);
int ft_setsockopt_sndtimeo(int *fd, int timeout, int verbose);
int ft_setsockopt_rcvtimeo(int *fd, int timeout, int verbose);

/*
 *  SOCK PCKT
 */

void ft_pckt_ip_opt_default(t_pckt_ip *opts);
void ft_pckt_ip_opt_set(t_pckt *pckt, t_pckt_ip *opts);

void ft_pckt_icmp_opt_default(t_pckt_icmp *opt);
void ft_pckt_icmp_opt_set(t_pckt *pckt, t_pckt_icmp *opts);

void ft_pckt_udp_opt_default(t_pckt_udp *opt);
void ft_pckt_udp_opt_set(t_pckt *pckt, t_pckt_udp *opts);

void ft_pckt_tcp_opt_default(t_pckt_tcp *opt);
void ft_pckt_tcp_opt_set(t_pckt *pckt, t_pckt_tcp *opt);

void ft_pckt_set_time(t_uchar *data);

void ft_sock_pckt_icmp(char *pckt, int pckt_len, t_sockaddr_in saddrin);
void ft_sock_pckt_udphdr(char *pckt, int pckt_len, t_sockaddr_in saddrin,
                         int port);
void ft_pckt_set_icmp(t_pckt *pckt, t_pckt_opt opt);
void ft_pckt_set_udphdr(t_pckt *pckt, t_pckt_opt opt);
void ft_pckt_set_tcphdr(t_pckt *pckt, t_pckt_opt opt);
void ft_pckt_tcphdr(t_pckt *pckt, t_pckt_opt opt);
int ft_pckt_ip_set(t_pckt *pckt, t_pckt_opt opt);

/*
 *  SOCK SOCKET
 */
int ft_socket_raw();
int ft_socket_icmp();

/*
 *  SOCK TOOLS
 */
unsigned short ft_checksum(void *b, int len);
char *ft_icmp_pr_type(int type);
char *ft_icmp_pr_code_unreach(int code);
char *ft_icmp_pr_code_redir(int code);
char *ft_icmp_pr_code_exc(int code);
void hexdump(void *mem, unsigned int len);

/*
 *  PCAP
 */

int ft_pcap_lookupdev(char **dev);
int ft_pcap_lookupnet(char *dev, bpf_u_int32 *net, bpf_u_int32 *mask);
int ft_pcap_open_live(pcap_t **handle, char *dev_name);
int ft_pcap_compile_setfilter(pcap_t *handle, char *dev_addr, t_bpf dev_net,
                              int port);

#endif
