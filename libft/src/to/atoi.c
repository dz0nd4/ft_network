/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:08:57 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:51 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_to.h"

int		ft_atoi(const char *nptr)
{
	int		i;
	int		nb;
	char	neg;

	i = 0;
	nb = 0;
	neg = '\0';
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		neg = nptr[i];
	i += neg ? 1 : 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	return (neg == '-' ? nb * (-1) : nb);
}
