/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnequ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:01 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	int i;

	i = -1;
	if (s1 && s2)
		while (++i < (int)n)
			if (s1[i] != s2[i])
				return (0);
	return (1);
}
