/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:47:05 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/25 11:33:53 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
#define FT_GET_NEXT_LINE_H

#include "../ft_libft_global.h"

#define GNL_BUFF_SIZE 3

typedef struct s_line {
  int fd;
  char *str;
  size_t index;
  struct s_line *next;
} t_line;

int get_next_line(const int fd, char **line);

#endif
