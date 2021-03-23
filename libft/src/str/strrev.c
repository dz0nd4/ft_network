/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:14:16 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:31:24 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "../put/ft_put.h"

char	*ft_strrev(char *s)
{
	size_t	len;
	size_t	i;
	char	c;

	if ((len = ft_strlen(s)) == 0)
		return (NULL);
	len -= 1;
	i = 0;
	c = '\0';
	while (i < len)
	{
		c = s[i];
		s[i++] = s[len];
		s[len--] = c;
	}
	return (s);
}
