/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:35 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:04 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memset(void *b, int c, size_t len)
{
    unsigned char *s;
    unsigned char set;

    s = (unsigned char *)b;
    set = (unsigned char)c;
    while (len-- > 0)
    {
        *s = set;
        s++;
    }
    return (b);
}
