/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstrpad_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:12:04 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:11:41 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putstrpad_fd(const char *s, size_t len, int fd)
{
	while (s && *s)
	{
		ft_putchar_fd(*s, fd);
		s++;
		len = (len == 0) ? 0 : len - 1;
	}
	while (len--)
		ft_putchar_fd('0', fd);
}
