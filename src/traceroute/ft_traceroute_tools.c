/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:13:35 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// int			ft_ipv4_to_struct(struct in_addr *addr, char *ipv4)
// {
// 	int domain;
// 	int	s;

// 	domain = AF_INET;
// 	s = inet_pton(domain, ipv4, addr);
// 	if (s <= 0) {
// 			if (s == 0)
// 					fprintf(stderr, "Not in presentation format\n");
// 			else
// 					perror("inet_pton");
// 			return(EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// char*			ft_struct_to_ipv4(struct in_addr *addr)
// {
// 	char *ipv4;

// 	if ((ipv4 = inet_ntoa(*addr)) == NULL) {
// 			perror("inet_ntop");
// 			return (NULL);
// 	}
// 	return (ipv4);
// }
