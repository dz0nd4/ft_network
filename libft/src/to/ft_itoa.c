/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:10:16 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:37:51 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_to.h"
# include "../put/ft_put.h"

char    	*ft_itoa(int input, char *buffer, int radix)
{
	size_t	i;
    char    sign;
    int     tmp;

	i = 0;
    sign = '\0';
    tmp = 0;
    if (input == 0)
        buffer[i++] = '0';
    if (input < 0)
    {
        sign = '-';
        input = -input;
    }
	while (input > 0)
    {
        tmp = (input % radix);
    	buffer[i++] = (tmp < 10) ? tmp + 48 : tmp + 87;
        input /= radix;
    }
    if (sign != '\0')
        buffer[i++] = sign;
    buffer[i] = '\0';
    return (ft_strrev(buffer));
}