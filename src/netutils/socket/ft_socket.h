/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/27 17:07:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SOCKET_H
#define FT_SOCKET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../../ft_net_global.h"

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

// typedef struct addrinfo t_addrinfo;
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

typedef struct msghdr t_msghdr;
typedef struct iovec t_iovec;

/*
 *  GET
 */
int ft_getaddrinfo(const char *host, t_addrinfo *result);

int ft_getnameinfo(t_sockaddr_in *host, char *name);
char *ft_getnameinfo_pr(t_sockaddr_in *host, char *hostname);
int ft_getnameinfo_err(const char *bin, const char *hostname);

/*
 *  INET
 */
int ft_inet_ntop(t_in_addr *src, char *dst);
int ft_inet_pton(t_in_addr *addr, char *ipv4);
int ft_inet_ntoa(t_in_addr *src, char *dst);

/*
 *  RECV
 */
int ft_recvmsg(int sfd, char *addr, char *packet, int packetlen);

/*
 *  SEND
 */
int ft_sendto(int fd, char *data, int datalen, t_sockaddr_in *saddrin);

/*
 *  SETSOCKOPT
 */
int ft_setsockopt_ttl(int *fd, int ttl, int verbose);
int ft_setsockopt_sndtimeo(int *fd, int timeout, int verbose);
int ft_setsockopt_rcvtimeo(int *fd, int timeout, int verbose);

/*
 *  SOCKET
 */
int ft_socket_raw();
int ft_socket_icmp();

#endif
