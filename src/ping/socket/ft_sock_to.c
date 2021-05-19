/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 15:48:19 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_sock_ntop
 *
 * Description:
 *    Abstraction over inet_ntop function.
 * 		It assumes 'ip' length is FT_ADDRSTRLEN
 * Returns:
 *    EXIT_SUCCESS or EXIT_FAILURE if inet_ntop fail
*/
int		ft_sock_ntop(t_in_addr *src, char *dst)
{
	// ft_bzero(dst, FT_ADDRSTRLEN);
	if (inet_ntop(AF_INET, src, dst, FT_ADDRSTRLEN) == NULL) {
      fprintf(stderr, "inet_ntop\n");
      return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
