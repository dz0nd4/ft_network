# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src_pckt.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:13:33 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIRS_PCKT = netutils/pckt

SUBFILES_PCKT = \
			netutils/pckt/ft_pckt_icmp.c \
			netutils/pckt/ft_pckt_ip.c \
			netutils/pckt/ft_pckt_tools.c \
			netutils/pckt/ft_pckt_udp.c \
			netutils/pckt/ft_pckt_tcp.c
