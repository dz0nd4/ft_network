# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src_pcap.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:16:47 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIRS_PCAP = netutils/pcap

SUBFILES_PCAP = \
			netutils/pcap/ft_pcap_compile.c \
			netutils/pcap/ft_pcap_lookup.c \
			netutils/pcap/ft_pcap_open.c