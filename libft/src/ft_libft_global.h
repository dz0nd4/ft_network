/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_global.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:43:25 by dz0nda            #+#    #+#             */
/*   Updated: 2021/08/09 12:06:10 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_GLOBAL_H
#define FT_LIBFT_GLOBAL_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libft.h"

#define FT_EXOK 0
#define FT_EXFAIL 1

#define FT_TRUE 1
#define FT_FALSE 0

typedef unsigned char t_uchar;

typedef struct s_arg {
  int i;
  int c;
  const char **v;
} t_arg;

typedef struct s_map_istr {
  int key;
  char *value;
} t_map_istr;

#endif
