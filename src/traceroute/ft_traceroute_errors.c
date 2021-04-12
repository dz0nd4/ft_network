/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/04/06 13:17:47 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int			ft_traceroute_help()
{
	printf("Usage:\n");
	printf(" <sudo> ft_traceroute host\n");
	return (EXIT_FAILURE);
}

int			ft_traceroute_perm()
{
	printf("/!\\ You don't have root privileges /!\\\n");
	return (ft_traceroute_help());
}

void ft_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void ft_traceroute_exit(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}
