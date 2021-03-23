/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:12:14 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:12:40 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	s[12];

	if (nb == 0)
		ft_putstr_fd("0", fd);
	else if (nb <= -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (nb >= 2147483647)
		ft_putstr_fd("2147483647", fd);
	else
	{
		ft_itoa(nb, s, 10);
		ft_putstr_fd(s, fd);
	}
}
