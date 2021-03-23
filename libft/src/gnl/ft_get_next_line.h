/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:47:05 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:36:18 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# define GNL_BUFF_SIZE 3

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../str/ft_str.h"

typedef struct		s_line
{
	int				fd;
	char			*str;
	size_t			index;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);
int					ft_get_input(char *file, char **input);

#endif
