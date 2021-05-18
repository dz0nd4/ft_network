# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/05/10 22:30:27 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/ping/src_ping.mk
include src/traceroute/src_traceroute.mk

SUBDIR = \
			network \
			${SUBDIRS_PING} \
			${SUBDIRS_TRACEROUTE} \
			nmap \

SUBFILE = \
			network/ft_network.c \
			\
			${SUBFILES_PING} \
			${SUBFILES_TRACEROUTE} \
			\
			nmap/ft_nmap.c \
