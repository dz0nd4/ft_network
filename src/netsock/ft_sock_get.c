/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 22:33:16 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

int    ft_sock_getaddrinfo(const char *host, t_addrinfo *host_addrinfo)
{
  int           sfd;
	t_addrinfo		hints;
	t_addrinfo		*result;
	t_addrinfo		*rp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = host_addrinfo->ai_family;
	hints.ai_socktype = host_addrinfo->ai_socktype;
	hints.ai_protocol = host_addrinfo->ai_protocol;

  if (getaddrinfo(host, NULL, (struct addrinfo *)&hints, (struct addrinfo **)&result) != 0)
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

	close(sfd);
	freeaddrinfo((struct addrinfo *)result);

  return (EXIT_SUCCESS);
}

/*
 * ft_sock_getnameinfo
 *
 * Description:
 *    Abstraction over ft_sock_getnameinfo function.
 * 		It assumes dst is FT_NI_MAXHOST length
 * Returns:
 *    The number of data read or -1
*/
int    ft_sock_getnameinfo(t_sockaddr_in *host, char *name)
{
    socklen_t len;
    char hbuf[FT_NI_MAXHOST];

    len = sizeof(t_sockaddr_in);

    if (getnameinfo((t_sockaddr *)host, len, hbuf, sizeof(hbuf), NULL, 0, FT_NI_NAMEREQD)) {
        // fprintf(stderr, "could not resolve hostname\n");
        // if (ft_sock_ntop((t_in_addr *)&host->sin_addr, hbuf) == EXIT_FAILURE)
	      //   return (FT_EXFAIL);
        ft_strcpy(name, hbuf);
        // s = malloc(sizeof(NI_MAXHOST));
    }
    else {
        ft_strcpy(name, hbuf);
    }

    return 0;
}
