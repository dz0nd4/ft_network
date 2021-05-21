/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_netsock.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 20:40:01 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NETSOCK_H
# define FT_NETSOCK_H

# include "../../libft/libft.h"

# define FT_EXOK      0
# define FT_EXFAIL    1
# define FT_NI_MAXHOST          1025
# define FT_ADDRSTRLEN 16

# include <sys/socket.h>
# include <sys/time.h>
# include <sys/types.h>

# include <time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <errno.h> 
# include <netdb.h>

# include <netinet/ip.h>
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define closesocket(s) close(s)

typedef int                 t_socket;
typedef struct sockaddr_in  t_sockaddr_in;
typedef struct sockaddr     t_sockaddr;
typedef struct in_addr      t_in_addr;
typedef struct addrinfo     t_addrinfo;
typedef struct ip           t_ip;
typedef struct udphdr       t_udp;
typedef struct icmp         t_icmp;
// typedef struct icmphdr      t_icmphdr;

typedef struct timeval      t_timeval;

typedef struct msghdr       t_msghdr;
typedef struct iovec        t_iovec;

typedef struct icmphdr
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


typedef struct  s_sock_icmp_type
{
  int   type_int;
  char  *type_str;
}               t_sock_icmp_type;

/*
 *  SOCK RECV
*/
int       ft_sock_recv(int fd, char *data, int datalen, t_sockaddr_in *saddrin);
int       ft_sock_recvmsg(int sfd, char *addr, char *packet, int packetlen);

/*
 *  SOCK SEND
*/
int    ft_sock_send(int fd, char *data, int datalen, t_sockaddr_in *saddrin);

/*
 *  SOCK TO
*/
int		    ft_sock_ntop(t_in_addr *src, char *dst);
int			  ft_sock_pton(struct in_addr *addr, char *ipv4);

/*
 *  SOCK GET
*/
int       ft_sock_getaddrinfo(const char *host, t_addrinfo *result);
int       ft_sock_getnameinfo(t_sockaddr_in *host, char *name);

/*
 *  SOCK TIME
*/
int		    ft_sock_gettime(t_timeval *tv);
int		    ft_sock_delay();
double    ft_sock_timediff(t_timeval *out, t_timeval *in);
double    ft_sock_getelapsedtime(t_timeval *in);

/*
 *  SOCK TOOLS
*/
unsigned short    ft_sock_cksum(void *b, int len);
char              *ft_sock_get_icmp_type(int type);
void              hexdump(void *mem, unsigned int len);

#endif
