/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 03:34:07 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/28 15:38:10 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_math.h"

/*
 * ft_sqrt
 *
 * Description:
 *    Calculate the Square Root of a Number with Newton-Raphson Method
 *     - Take a reasonable guess (approximate root) for the square root
 *     - Add the approximate root with the original number divided by the
 * approximate root and divide by 2.
 *     - Continue step 2 until the difference in the approximate root along the
 * iterations is less than the precision value
 *
 * Returns:
 *  The approximate square root number
 */
double ft_sqrt(double num) {
  const int max_i = 10;
  int i = 0;
  double sqrt = 0;
  double tmp = 0;

  sqrt = num;  //   sqrt = num / 2;

  while (i < max_i && tmp != sqrt) {
    tmp = sqrt;
    sqrt = (sqrt + num / sqrt) / 2;
    i++;
  }

  return (sqrt);
}