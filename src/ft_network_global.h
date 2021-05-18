/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_network_global.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:14:00 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 03:04:27 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NETWORK_GLOBAL_H
# define FT_NETWORK_GLOBAL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <string.h>

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

# define FT_SUCCESS   0
# define FT_FAILURE   1

# define FT_EXOK      0
# define FT_EXFAIL    1

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
typedef struct icmphdr      t_icmphdr;

typedef struct timeval t_timeval;

typedef struct msghdr       t_msghdr;
typedef struct iovec        t_iovec;

#endif
