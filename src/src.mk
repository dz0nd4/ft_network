# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/08/27 15:54:19 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/net/src_net.mk
include src/netutils/src_netutils.mk
include src/ping/src_ping.mk

SUBDIR = \
			${SUBDIRS_NET} \
			${SUBDIRS_NETUTILS} \
			${SUBDIRS_PING}

SUBFILE = \
			${SUBFILES_NET} \
			${SUBFILES_NETUTILS} \
			${SUBFILES_PING}