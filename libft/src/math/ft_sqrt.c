/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 03:34:07 by dzonda            #+#    #+#             */
/*   Updated: 2021/06/10 15:07:03 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

double ft_sqrt(double num) {
  double tmp;
  double sqrt;

  sqrt = num / 2;
  tmp = 0;

  while (sqrt != tmp) {
    tmp = sqrt;
    sqrt = (num / tmp + tmp) / 2;
  }

  return (sqrt);
}