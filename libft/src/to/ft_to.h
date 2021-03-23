/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 03:38:51 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:33:09 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TO_H
# define FT_TO_H

# include "../is/ft_is.h"
# include "../str/ft_str.h"

int		ft_atoi(const char *nptr);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_itoa(int input, char *buffer, int radix);
size_t	ft_nbrlen(int n);

#endif
