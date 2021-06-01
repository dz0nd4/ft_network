/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_socket_tools.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:12:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// int ft_tr_resolve(t_sockaddr_in *from, char *name)
// {
//     struct sockaddr_in sa;    /* input */
//     socklen_t len;         /* input */
//     char hbuf[FT_NI_MAXHOST];

//     memset(&sa, 0, sizeof(struct sockaddr_in));

//     char *s = NULL;

//     /* For IPv4*/
//     sa.sin_family = AF_INET;
//     sa.sin_addr.s_addr = inet_addr(inet_ntoa(from->sin_addr));
//     len = sizeof(struct sockaddr_in);

//     if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
//         NULL, 0, NI_NAMEREQD)) {
//         // printf("could not resolve hostname\n");
//         // s = malloc(sizeof(NI_MAXHOST));
//         ft_strcpy(name, inet_ntoa(from->sin_addr));

//     }
//     else {
//         // printf("host=%s\n", hbuf);
//         // s = malloc(sizeof(NI_MAXHOST));
//         ft_strcpy(name, hbuf);
//     }

//     return 0;
// }

