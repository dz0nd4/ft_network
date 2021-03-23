/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendlpad_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:11:59 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:12:45 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putendlpad_fd(const char *s, size_t len, int fd)
{
	if (s)
	{
		ft_putstrpad_fd(s, len, fd);
		ft_putchar_fd('\n', fd);
	}
}
