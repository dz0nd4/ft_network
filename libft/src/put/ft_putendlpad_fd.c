/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl_fd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:11:59 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:38:10 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_put.h"

void	ft_putendlpad_fd(const char *s, size_t len, int fd)
{
	if (s)
	{
		ft_putstrpad_fd(s, len, fd);
		ft_putchar_fd('\n', fd);
	}
}
