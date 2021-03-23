/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbrendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:12:04 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:12:38 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putnbrendl_fd(int nb, int fd)
{
	ft_putnbr_fd(nb, fd);
	ft_putchar_fd('\n', fd);
}
