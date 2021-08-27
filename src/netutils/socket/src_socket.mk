# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src_socket.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:13:14 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIRS_SOCKET = netutils/socket

SUBFILES_SOCKET = \
			netutils/socket/ft_sock_icmp.c \
			netutils/socket/ft_sock_socket.c \
			netutils/socket/ft_recvmsg.c \
			netutils/socket/ft_recvfrom.c \
			netutils/socket/ft_sock_opt.c \
			netutils/socket/ft_sock_send.c \
			netutils/socket/ft_sock_to.c	\
			netutils/socket/ft_getaddrinfo.c \
			netutils/socket/ft_getnameinfo.c \
			netutils/socket/ft_getifaddr.c \
			netutils/socket/ft_getservbyport.c
