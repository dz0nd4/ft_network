/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_tools.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 23:10:57 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int    ft_socket_recv(int fd, char *data, int datalen, t_sockaddr_in *saddrin)
{
	int saddrin_size;
	int i;

	saddrin_size = sizeof(t_sockaddr);
	i = recvfrom(fd, data, datalen, 0, (t_sockaddr *)saddrin, &saddrin_size);
	if (i <= 0)
		return (-1);
	// if (i < 0) {
	// 	ft_exit("sendto()");
	// }
	return (i);
}

int    ft_socket_send(int fd, char *data, int datalen, t_sockaddr_in *saddrin)
{
	int i;

	i = sendto(fd, data, datalen, 0, (t_sockaddr *)saddrin, sizeof(t_sockaddr));
	if (i <= 0) {
		perror("sendto");
		return (EXIT_FAILURE);
	}
	// if (i < 0) {
	// 	ft_exit("sendto()");
	// }
	return (EXIT_SUCCESS);
}

int    ft_socket_getaddrinfo(const char *host, t_addrinfo *host_addrinfo)
{
  int           sfd;
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP; // ! should be change

  if (getaddrinfo(host, NULL, &hints, &result) != 0)
    return (EXIT_FAILURE);

  rp = result;
	while (rp != NULL) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd != INVALID_SOCKET)
			break;
		rp = rp->ai_next;
	}
	if (rp == NULL)
		return (EXIT_FAILURE);
  
	ft_memcpy(host_addrinfo, rp, sizeof(t_addrinfo));

	freeaddrinfo(result);

  return (EXIT_SUCCESS);
}

int ft_tr_resolve(t_sockaddr_in *from, char *name)
{
    struct sockaddr_in sa;    /* input */
    socklen_t len;         /* input */
    char hbuf[FT_NI_MAXHOST];

    memset(&sa, 0, sizeof(struct sockaddr_in));

    char *s = NULL;

    /* For IPv4*/
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(inet_ntoa(from->sin_addr));
    len = sizeof(struct sockaddr_in);

    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
        NULL, 0, NI_NAMEREQD)) {
        // printf("could not resolve hostname\n");
        // s = malloc(sizeof(NI_MAXHOST));
        ft_strcpy(name, inet_ntoa(from->sin_addr));

    }
    else {
        // printf("host=%s\n", hbuf);
        // s = malloc(sizeof(NI_MAXHOST));
        ft_strcpy(name, hbuf);
    }

    return 0;
}

int			ft_ipv4_to_struct(t_in_addr *addr, char *ipv4)
{
	int domain;
	int	s;

	domain = AF_INET;
	s = inet_pton(domain, ipv4, addr);
	if (s <= 0) {
			if (s == 0)
					fprintf(stderr, "Not in presentation format\n");
			else
					perror("inet_pton");
			return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// char*			ft_struct_to_ipv4(struct in_addr *addr)
// {
// 	char *ipv4;

// 	if ((ipv4 = inet_ntoa(*addr)) == NULL) {
// 			perror("inet_ntop");
// 			return (NULL);
// 	}
// 	return (ipv4);
// }
