/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 14:23:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_sock_ntop
 *
 * Description:
 *    Abstraction over inet_ntop function.
 * 		It assumes 'ip' length is FT_ADDRSTRLEN
 * 		NUMERIC to PRINTABLE
 * Returns:
 *    EXIT_SUCCESS or EXIT_FAILURE if inet_ntop fail
*/
int		ft_sock_ntop(t_in_addr *src, char *dst)
{
	if (inet_ntop(AF_INET, src, dst, FT_ADDRSTRLEN) == NULL) {
      fprintf(stderr, "inet_ntop\n");
      return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			ft_sock_pton(t_in_addr *addr, char *ipv4)
{
	int domain;
	int	s;

	domain = AF_INET;
	s = inet_pton(domain, ipv4, addr);
	if (s <= 0) {
			// if (s == 0)
			// 		fprintf(stderr, "Not in presentation format\n");
			// else
			// 		perror("inet_pton");
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
