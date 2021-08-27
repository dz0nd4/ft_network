# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:08:03 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/net/src_net.mk
include src/netutils/src_netutils.mk
include src/nmap/src_nmap.mk
include src/ping/src_ping.mk
include src/traceroute/src_traceroute.mk

SUBDIR = \
			${SUBDIRS_NET} \
			${SUBDIRS_NETUTILS} \
			${SUBDIRS_NMAP} \
			${SUBDIRS_PING} \
			${SUBDIRS_TRACEROUTE}

SUBFILE = \
			${SUBFILES_NET} \
			${SUBFILES_NETUTILS} \
			${SUBFILES_NMAP} \
			${SUBFILES_PING} \
			${SUBFILES_TRACEROUTE}