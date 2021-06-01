/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 22:44:20 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_inet_ntop
 *
 * Description:
 *    Abstraction over inet_ntop function.
 * 		It assumes 'ip' length is FT_ADDRSTRLEN
 * 		NUMERIC to PRINTABLE
 * Returns:
 *    FT_EXOK or FT_EXFAIL if inet_ntop fail
*/
int		ft_inet_ntop(t_in_addr *src, char *dst)
{
	if (inet_ntop(AF_INET, src, dst, FT_ADDRSTRLEN) == NULL) {
      fprintf(stderr, "inet_ntop\n");
      return(FT_EXFAIL);
	}
	return (FT_EXOK);
}

int			ft_inet_pton(t_in_addr *addr, char *ipv4)
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
			return(FT_EXFAIL);
	}
	return (FT_EXOK);
}

int		ft_inet_ntoa(t_in_addr *src, char *dst)
{
	if ((dst = inet_ntoa(*src)) == NULL) {
			perror("inet_ntoa");
			return (FT_EXFAIL);
	}
	return (FT_EXOK);
}
