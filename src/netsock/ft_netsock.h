/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_netsock.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 00:46:31 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NETSOCK_H
# define FT_NETSOCK_H

# include "../../libft/libft.h"

// # define FT_EXOK      0
// # define FT_EXFAIL    1
# define FT_NI_MAXHOST          1025
# define FT_ADDRSTRLEN 16


# include <stdio.h>

# include <sys/time.h>

# include <sys/types.h>
# include <sys/socket.h>

# include <time.h>
// # include <errno.h> 
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define closesocket(s) close(s)

# define FT_IPHDR_LEN                 sizeof(t_ip)
# define FT_ICMPHDR_LEN               8
# define FT_TIMEVAL_LEN               16
# define FT_PING_ICMPHDR              FT_IPHDR_LEN + FT_ICMPHDR_LEN

typedef int                 t_socket;
typedef struct sockaddr_in  t_sockaddr_in;
typedef struct sockaddr     t_sockaddr;
typedef struct in_addr      t_in_addr;
// typedef struct addrinfo     t_addrinfo;
typedef struct udphdr       t_udp;
typedef struct icmp         t_icmp;
// typedef struct icmphdr      t_icmphdr;

typedef struct timeval      t_timeval;

typedef struct msghdr       t_msghdr;
typedef struct iovec        t_iovec;



/*
 *  INTEROPERABILITY
*/

#ifdef __APPLE__

# define FT_SOL_SOCKET    SOL_SOCKET // IPPROTO_IP
# define FT_NI_NAMEREQD	  8	/* Don't return numeric addresses.  */

typedef struct ip           t_ip;

typedef struct s_icmphdr
{
  u_int8_t type;                /* message type */
  u_int8_t code;                /* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t        id;
      u_int16_t        sequence;
    } echo;                        /* echo datagram */
    u_int32_t        gateway;        /* gateway address */
    struct
    {
      u_int16_t        unused;
      u_int16_t        mtu;
    } frag;                        /* path mtu discovery */
  } un;
}     t_icmphdr;

typedef struct s_addrinfo {
	int	ai_flags;	/* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
	int	ai_family;	/* PF_xxx */
	int	ai_socktype;	/* SOCK_xxx */
	int	ai_protocol;	/* 0 or IPPROTO_xxx for IPv4 and IPv6 */
	socklen_t ai_addrlen;	/* length of ai_addr */
	char	*ai_canonname;	/* canonical name for hostname */
	struct	sockaddr *ai_addr;	/* binary address */
	struct	s_addrinfo *ai_next;	/* next structure in linked list */
}           t_addrinfo;

// typedef struct s_addrinfo
// {
//   int ai_flags;			/* Input flags.  */
//   int ai_family;		/* Protocol family for socket.  */
//   int ai_socktype;		/* Socket type.  */
//   int ai_protocol;		/* Protocol for socket.  */
//   socklen_t ai_addrlen;		/* Length of socket address.  */
//   struct sockaddr *ai_addr;	/* Socket address for socket.  */
//   char *ai_canonname;		/* Canonical name for service location.  */
//   struct s_addrinfo *ai_next;	/* Pointer to next in list.  */
// }             t_addrinfo;

#endif

#ifdef __linux__

# define FT_SOL_SOCKET    SOL_SOCKET
# define FT_NI_NAMEREQD	  8	/* Don't return numeric addresses.  */

typedef struct icmphdr  t_icmphdr;
// typedef struct addrinfo t_addrinfo;
typedef struct ip           t_ip;

typedef struct s_addrinfo
{
  int ai_flags;			/* Input flags.  */
  int ai_family;		/* Protocol family for socket.  */
  int ai_socktype;		/* Socket type.  */
  int ai_protocol;		/* Protocol for socket.  */
  socklen_t ai_addrlen;		/* Length of socket address.  */
  struct sockaddr *ai_addr;	/* Socket address for socket.  */
  char *ai_canonname;		/* Canonical name for service location.  */
  struct s_addrinfo *ai_next;	/* Pointer to next in list.  */
}       t_addrinfo;

// typedef struct s_ip
//   {
// #if __BYTE_ORDER == __LITTLE_ENDIAN
//     unsigned int ip_hl:4;		/* header length */
//     unsigned int ip_v:4;		/* version */
// #endif
// #if __BYTE_ORDER == __BIG_ENDIAN
//     unsigned int ip_v:4;		/* version */
//     unsigned int ip_hl:4;		/* header length */
// #endif
//     uint8_t ip_tos;			/* type of service */
//     unsigned short ip_len;		/* total length */
//     unsigned short ip_id;		/* identification */
//     unsigned short ip_off;		/* fragment offset field */
// #define	FT_IP_RF 0x8000			/* reserved fragment flag */
// #define	FT_IP_DF 0x4000			/* dont fragment flag */
// #define	FT_IP_MF 0x2000			/* more fragments flag */
// #define	FT_IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
//     uint8_t ip_ttl;			/* time to live */
//     uint8_t ip_p;			/* protocol */
//     unsigned short ip_sum;		/* checksum */
//     struct in_addr ip_src, ip_dst;	/* source and dest address */
// }       t_ip;

#endif

typedef struct  s_sock_icmp_type
{
  int   type_int;
  char  *type_str;
}               t_sock_icmp_type;

/*
 *  SOCK RECV
*/
int       ft_recvfrom(int fd, char *data, int datalen, t_sockaddr_in *saddrin);
int       ft_recvmsg(int sfd, char *addr, char *packet, int packetlen);

/*
 *  SOCK SEND
*/
int    ft_sendto(int fd, char *data, int datalen, t_sockaddr_in *saddrin);

/*
 *  SOCK TO
*/
int		    ft_inet_ntop(t_in_addr *src, char *dst);
int			  ft_inet_pton(struct in_addr *addr, char *ipv4);
int		    ft_inet_ntoa(t_in_addr *src, char *dst);

/*
 *  SOCK GET
*/
int       ft_getaddrinfo(const char *host, t_addrinfo *result);
int       ft_getnameinfo(t_sockaddr_in *host, char *name);

/*
 *  SOCK TIME
*/
int		    ft_gettimeofday(t_timeval *tv);
int		    ft_delay();
double    ft_timediff(t_timeval *out, t_timeval *in);
double    ft_getelapsedtime(t_timeval *in);


int       ft_setsockopt_ttl(int *fd, int ttl, int verbose);
int       ft_setsockopt_sndtimeo(int *fd, int timeout, int verbose);
int       ft_setsockopt_rcvtimeo(int *fd, int timeout, int verbose);

/*
 *  SOCK TOOLS
*/
unsigned short    ft_sock_cksum(void *b, int len);
char              *ft_sock_get_icmp_type(int type);
void              hexdump(void *mem, unsigned int len);

#endif
