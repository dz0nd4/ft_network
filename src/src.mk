# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/03/26 15:49:23 by dzonda           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIR = \
			network \
			traceroute \
			nmap \

SUBFILE = \
			network/ft_network.c \
			\
			traceroute/ft_traceroute.c \
			traceroute/ft_traceroute_init.c \
			traceroute/ft_traceroute_send.c \
			\
			nmap/ft_nmap.c \
