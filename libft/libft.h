/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:43:25 by dz0nda            #+#    #+#             */
/*   Updated: 2021/08/28 13:15:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "./src/ft_libft_global.h"

/*
 * BOOLEANS
 */
#define FT_EXOK 0
#define FT_EXFAIL 1

#define FT_TRUE 1
#define FT_FALSE 0

/*
 * VARIABLES MAX SIZE
 */
#define FT_UINT8_MAX 0xFF    /* 255 */
#define FT_UINT16_MAX 0xFFFF /* 65535 */

/*
 * STRUCTURES
 */
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
