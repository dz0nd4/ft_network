/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthexa_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:12:14 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:12:43 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_puthexa_fd(int nb, int fd)
{
	char	s[12];

	ft_putstr("0x");
	if (nb <= 0 || nb > 2147483647)
		ft_putstr_fd("00", fd);
	else
	{
		ft_itoa(nb, s, 16);
		ft_putstr_fd(s, fd);
	}
}
