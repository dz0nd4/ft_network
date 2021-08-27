# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src_netutils.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:12:35 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/netutils/socket/src_socket.mk
include src/netutils/tools/src_tools.mk
include src/netutils/pcap/src_pcap.mk
include src/netutils/pckt/src_pckt.mk

SUBDIRS_NETUTILS = \
			netutils \
			${SUBDIRS_SOCKET} \
			${SUBDIRS_TOOLS} \
			${SUBDIRS_PCKT} \
			${SUBDIRS_PCAP}

SUBFILES_NETUTILS = \
			${SUBFILES_SOCKET} \
			${SUBFILES_TOOLS} \
			${SUBFILES_PCKT} \
			${SUBFILES_PCAP}