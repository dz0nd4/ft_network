/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isblank.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:09:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:37:45 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_is.h"

int		ft_isblank(int c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}