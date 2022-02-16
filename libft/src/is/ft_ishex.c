/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:09:20 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/09 09:44:11 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is.h"

int ft_ishex(int c) {
  return (ft_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

int ft_ishexstr(const char *str) {
  while (*str) {
    if (!ft_ishex(*str)) return (FT_FALSE);
    str++;
  }
  return (FT_TRUE);
}
