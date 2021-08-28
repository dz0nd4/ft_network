# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src_socket.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/08/27 16:48:57 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIRS_SOCKET = netutils/socket

SUBFILES_SOCKET = \
			netutils/socket/ft_getaddrinfo.c \
			netutils/socket/ft_getnameinfo.c \
			netutils/socket/ft_inet.c	\
			netutils/socket/ft_recvmsg.c \
			netutils/socket/ft_sendto.c \
			netutils/socket/ft_setsockopt.c \
			netutils/socket/ft_socket.c
