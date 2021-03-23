/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:13:02 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char			*ft_strdup(const char *s1)
{
	int			i;
	size_t		len;
	char		*dest;

	i = -1;
	if ((len = ft_strlen(s1)) == 0)
		return (NULL);
	if ((dest = ft_strnew(len)) == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	return (dest);
}
