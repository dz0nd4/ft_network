/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:12:14 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:13 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_put.h"

void		ft_puthexapad_fd(int nb, size_t len, int fd)
{
    char	s[12];

    ft_putstr("0x");
    len = (len > 2) ? len - 2 : 0;
    if (nb <= 0 || nb > 2147483647)
        ft_putstrpad_fd("00", len, fd);
    else
    {
        ft_itoa(nb, s, 16);
        ft_putstrpad_fd(s, len, fd);
    }
}
