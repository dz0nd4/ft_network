/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/18 22:02:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int  ft_ping_exit(char *s)
{
	// perror(s);
  fprintf(stderr, "Error: %s\n", s);
	return(EXIT_FAILURE);
}

int  ft_ping_usage()
{
	fprintf(stderr, "Usage: ping [-ahv] destination\n");
	return(EXIT_FAILURE);
}

int  ft_ping_error_host(const char *dst)
{
	fprintf(stderr, "%s: Échec temporaire dans la résolution du nom\n", dst);
	return(EXIT_FAILURE);
}