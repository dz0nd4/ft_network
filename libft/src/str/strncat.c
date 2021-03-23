/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:13:47 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(s1);
	while (++i < n && s2[i])
		s1[len + i] = s2[i];
	s1[len + i] = '\0';
	return (s1);
}
