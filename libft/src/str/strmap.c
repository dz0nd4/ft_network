/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:13:37 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:14:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	size_t	i;

	i = -1;
	if (s)
	{
		if ((str = ft_strnew(ft_strlen(s))) == NULL)
			return (NULL);
		while (s[++i])
			str[i] = f(str[i]);
		return (str);
	}
	return (NULL);
}
